/*!
 * @brief	モデルシェーダー。
 */


/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//アルベドテクスチャ。
Texture2D<float4> albedoTexture : register(t0);	
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t1);
//シャドウマップ。
Texture2D<float4> g_shadowMap : register(t2);	
//法線マップ。
Texture2D<float4> normalMap : register(t3);
//スペキュラマップ。
Texture2D<float4> specularMap : register(t4);
/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// 定数バッファ。
/////////////////////////////////////////////////////////////
/*!
 * @brief	頂点シェーダーとピクセルシェーダー用の定数バッファ。
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	//todo ライトビュー行列を追加。
	float4x4 mLightView;	//ライトビュー行列。
	float4x4 mLightProj;	//ライトプロジェクション行列。
	int isShadowReciever;	//シャドウレシーバーフラグ。
	int isHasNormalMap;     //法線マップのフラグ。
	int isHasSpecuraMap;    //スペキュラマップのフラグ。
};
static const int NUM_DIRECTION_LIGHT = 4;
/*!
*@brief	ライト用の定数バッファ。
*/
cbuffer LightCb : register(b1) {
	float4 dligDirection[NUM_DIRECTION_LIGHT];
	float4 dligColor[NUM_DIRECTION_LIGHT];
	float4 eyePos[NUM_DIRECTION_LIGHT];
	float4 specPow[NUM_DIRECTION_LIGHT];
	float envPow;
};
static const int NUM_POINT_LIGHT = 5;

struct SPointLight {
	float4	position[NUM_POINT_LIGHT];		//位置。
	float4	color[NUM_POINT_LIGHT];			//カラー。
	float4	attn[NUM_POINT_LIGHT];			//減衰定数。(xを小さくするとライトの明るさが増す、yとzを小さくするとライトが遠くまで届くようになる。)
};

cbuffer PointLightCb : register(b2) {
	SPointLight pointLights;
};

/// <summary>
/// シャドウマップ用の定数バッファ。
/// </summary>
cbuffer ShadowMapCb : register(b1) {
	float4x4 lightViewProjMatrix;	//ライトビュープロジェクション行列。
}
/////////////////////////////////////////////////////////////
//各種構造体
/////////////////////////////////////////////////////////////
/*!
 * @brief	スキンなしモデルの頂点構造体。
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float3 Tangent  : TANGENT;				//接ベクトル。
    float2 TexCoord : TEXCOORD0;			//UV座標。
};
/*!
 * @brief	スキンありモデルの頂点構造体。
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float2 TexCoord	: TEXCOORD0;			//UV座標。
    float3 Tangent	: TANGENT;				//接ベクトル。
    uint4  Indices  : BLENDINDICES0;		//この頂点に関連付けされているボーン番号。x,y,z,wの要素に入っている。4ボーンスキニング。
    float4 Weights  : BLENDWEIGHT0;			//この頂点に関連付けされているボーンへのスキンウェイト。x,y,z,wの要素に入っている。4ボーンスキニング。
};

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float4 posInLVP		: TEXCOORD1;	//ライトビュープロジェクション空間での座標。
	float3 WorldPos	    : TEXCOORD2;	//ワールド座標。
};
/// <summary>
/// シャドウマップ用のピクセルシェーダへの入力構造体。
/// </summary>
struct PSInput_ShadowMap {
	float4 Position 			: SV_POSITION;	//座標。
};
/*!
 *@brief	スキン行列を計算。
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	float4 worldPos = mul(mWorld, In.Position);

	psInput.WorldPos = worldPos;

	psInput.Position = mul(mView, worldPos);
	psInput.Position = mul(mProj, psInput.Position);


	if (isShadowReciever == 1) {
		//続いて、ライトビュープロジェクション空間に変換。
		psInput.posInLVP = mul(mLightView, worldPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}

	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	スキンありモデル用の頂点シェーダー。
 * 全ての頂点に対してこのシェーダーが呼ばれる。
 * Inは1つの頂点データ。VSInputNmTxWeightsを見てみよう。
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
	        skinning += boneMatrix[ In.Indices[i] ] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //最後のボーンを計算する。
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
	    pos = mul(skinning, In.Position);
		psInput.WorldPos = pos;
	}
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );

	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
    return psInput;
}
//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain(PSInput In) : SV_Target0
{
	//albedoテクスチャからカラーをフェッチする。
	float4 albedo = albedoTexture.Sample(
		Sampler,
		In.TexCoord
	);

	//法線を計算する。
	float3 normal = 0;
	if (isHasNormalMap == 1) {
		//法線マップがある。
		//法線と接ベクトルの外積を計算して、従ベクトルを計算する。
		float3 biNormal = cross(In.Normal, In.Tangent);
		normal = normalMap.Sample(Sampler, In.TexCoord);
		//0.0～1.0の範囲になっているタンジェントスペース法線を
		//-1.0～1.0の範囲に変換する。
		normal = (normal * 2.0f) - 1.0f;
		//法線をタンジェントスペースから、ワールドスペースに変換する。
		normal = In.Tangent * normal.x + biNormal * normal.y + In.Normal * normal.z;
	}
	else {
		//ない。
		normal = In.Normal;
	}
	
	float3 lig = 0.0f;
	//ポイントライトを計算。
	float3 ligDir[NUM_POINT_LIGHT];
	for (int i = 0; i < NUM_POINT_LIGHT; i++) {
		ligDir[i] = normalize(In.WorldPos - pointLights.position[i].xyz);

		float distance = length(In.WorldPos - pointLights.position[i].xyz);

		float t = max(0.0f, dot(-ligDir[i], normal));

		float affect = 1.0f - min(1.0f, distance / pointLights.attn[i].x);

		lig += pointLights.color[i] * t * affect;
	}
	//ディレクションライトの拡散反射光を計算する。
	for (int i = 0; i < NUM_DIRECTION_LIGHT; i++) {
		lig += max(0.0f, dot(normal, ligDir[i + 1].xyz * -1.0f)) * dligColor[i];
	}

	//スペキュラライト。
	for (int i = 0; i < NUM_DIRECTION_LIGHT; i++) {
		//視線ベクトルを求める。
		float3 E = normalize(eyePos[i] - In.WorldPos);
		//反射ベクトルを求める。
		float3 R = -E + 2 * dot(normal, E) * normal;
		//ライトの方向と、反射ベクトルの内積を求める。
		float3 D = dot(-1.0f * ligDir[i + 1].xyz, R);
		float t = max(0.0f, D);
		float specPower = 1.0f;
		if (isHasSpecuraMap == 1) {
			specPower = specularMap.Sample(Sampler, In.TexCoord).r;
		}
		float3 F = pow(t, 2.0f) * pointLights.color[i] * dligColor[i] * specPower *1.0f; //dligColor[i].xyz * pow(t, /*specPow[i]*/specPower.x);
		lig += F;
	}

	if (isShadowReciever == 1) {	//シャドウレシーバー。
									//LVP空間から見た時の最も手前の深度値をシャドウマップから取得する。
		float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
		shadowMapUV *= float2(0.5f, -0.5f);
		shadowMapUV += 0.5f;
		//シャドウマップの範囲内かどうかを判定する。
		if (shadowMapUV.x < 1.0f
			&& shadowMapUV.x > 0.0f
			&& shadowMapUV.y < 1.0f
			&& shadowMapUV.y > 0.0f
			) {

			///LVP空間での深度値を計算。
			float zInLVP = In.posInLVP.z / In.posInLVP.w;
			//シャドウマップに書き込まれている深度値を取得。
			float zInShadowMap = g_shadowMap.Sample(Sampler, shadowMapUV);

			if (zInLVP > zInShadowMap + 0.001f) {
				//影が落ちているので、光を弱くする
				lig *= 0.5f/* = float4(1.0f, 0.0f, 0.0f, 1.0f)*/;
			}
		}
	}
	lig += float4(0.5f, 0.5f, 0.5f, 1.0f);
	float4 final;
	final.xyz = albedo.xyz *lig;
	return float4(final.xyz, 1.0f);
}
/// <summary>
/// シャドウマップ生成用の頂点シェーダー。
/// </summary>
PSInput_ShadowMap VSMain_ShadowMap(VSInputNmTxVcTangent In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}
/// <summary>
/// シャドウマップ生成用の頂点シェーダー。
/// </summary>
PSInput_ShadowMap VSMain_ShadowMapSkin(VSInputNmTxWeights In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4x4 worldMatrix = 0;
	float4 pos = 0;
	
	//この頂点のワールド行列を計算する。
	float w = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		//boneMatrixにボーン行列が設定されていて、
		//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
		//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
		worldMatrix += boneMatrix[In.Indices[i]] * In.Weights[i];
		w += In.Weights[i];
	}
	//最後のボーンを計算する。
	worldMatrix += boneMatrix[In.Indices[3]] * (1.0f - w);

	//頂点座標に計算したワールド行列を乗算して、頂点をワールド空間に変換。
	pos = mul(worldMatrix, In.Position);

	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}
/// <summary>
/// ピクセルシェーダーのエントリ関数。
/// </summary>
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//射影空間でのZ値を返す。
	return In.Position.z / In.Position.w;
}