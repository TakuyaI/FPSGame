/*!
 * @brief	���f���V�F�[�_�[�B
 */


/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//�A���x�h�e�N�X�`���B
Texture2D<float4> albedoTexture : register(t0);	
//�{�[���s��
StructuredBuffer<float4x4> boneMatrix : register(t1);
//�V���h�E�}�b�v�B
Texture2D<float4> g_shadowMap : register(t2);	
//�@���}�b�v�B
Texture2D<float4> normalMap : register(t3);
//�X�y�L�����}�b�v�B
Texture2D<float4> specularMap : register(t4);
/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// �萔�o�b�t�@�B
/////////////////////////////////////////////////////////////
/*!
 * @brief	���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�B
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	//todo ���C�g�r���[�s���ǉ��B
	float4x4 mLightView;	//���C�g�r���[�s��B
	float4x4 mLightProj;	//���C�g�v���W�F�N�V�����s��B
	int isShadowReciever;	//�V���h�E���V�[�o�[�t���O�B
	int isHasNormalMap;     //�@���}�b�v�̃t���O�B
	int isHasSpecuraMap;    //�X�y�L�����}�b�v�̃t���O�B
};
static const int NUM_DIRECTION_LIGHT = 4;
/*!
*@brief	���C�g�p�̒萔�o�b�t�@�B
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
	float4	position[NUM_POINT_LIGHT];		//�ʒu�B
	float4	color[NUM_POINT_LIGHT];			//�J���[�B
	float4	attn[NUM_POINT_LIGHT];			//�����萔�B(x������������ƃ��C�g�̖��邳�������Ay��z������������ƃ��C�g�������܂œ͂��悤�ɂȂ�B)
};

cbuffer PointLightCb : register(b2) {
	SPointLight pointLights;
};

/// <summary>
/// �V���h�E�}�b�v�p�̒萔�o�b�t�@�B
/// </summary>
cbuffer ShadowMapCb : register(b1) {
	float4x4 lightViewProjMatrix;	//���C�g�r���[�v���W�F�N�V�����s��B
}
/////////////////////////////////////////////////////////////
//�e��\����
/////////////////////////////////////////////////////////////
/*!
 * @brief	�X�L���Ȃ����f���̒��_�\���́B
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float3 Tangent  : TANGENT;				//�ڃx�N�g���B
    float2 TexCoord : TEXCOORD0;			//UV���W�B
};
/*!
 * @brief	�X�L�����胂�f���̒��_�\���́B
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float2 TexCoord	: TEXCOORD0;			//UV���W�B
    float3 Tangent	: TANGENT;				//�ڃx�N�g���B
    uint4  Indices  : BLENDINDICES0;		//���̒��_�Ɋ֘A�t������Ă���{�[���ԍ��Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
    float4 Weights  : BLENDWEIGHT0;			//���̒��_�Ɋ֘A�t������Ă���{�[���ւ̃X�L���E�F�C�g�Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
};

/*!
 * @brief	�s�N�Z���V�F�[�_�[�̓��́B
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float4 posInLVP		: TEXCOORD1;	//���C�g�r���[�v���W�F�N�V������Ԃł̍��W�B
	float3 WorldPos	    : TEXCOORD2;	//���[���h���W�B
};
/// <summary>
/// �V���h�E�}�b�v�p�̃s�N�Z���V�F�[�_�ւ̓��͍\���́B
/// </summary>
struct PSInput_ShadowMap {
	float4 Position 			: SV_POSITION;	//���W�B
};
/*!
 *@brief	�X�L���s����v�Z�B
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
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	float4 worldPos = mul(mWorld, In.Position);

	psInput.WorldPos = worldPos;

	psInput.Position = mul(mView, worldPos);
	psInput.Position = mul(mProj, psInput.Position);


	if (isShadowReciever == 1) {
		//�����āA���C�g�r���[�v���W�F�N�V������Ԃɕϊ��B
		psInput.posInLVP = mul(mLightView, worldPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}

	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
 * �S�Ă̒��_�ɑ΂��Ă��̃V�F�[�_�[���Ă΂��B
 * In��1�̒��_�f�[�^�BVSInputNmTxWeights�����Ă݂悤�B
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
			//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
			//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
	        skinning += boneMatrix[ In.Indices[i] ] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //�Ō�̃{�[�����v�Z����B
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
		//mul�͏�Z���߁B
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
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain(PSInput In) : SV_Target0
{
	//albedo�e�N�X�`������J���[���t�F�b�`����B
	float4 albedo = albedoTexture.Sample(
		Sampler,
		In.TexCoord
	);

	//�@�����v�Z����B
	float3 normal = 0;
	if (isHasNormalMap == 1) {
		//�@���}�b�v������B
		//�@���Ɛڃx�N�g���̊O�ς��v�Z���āA�]�x�N�g�����v�Z����B
		float3 biNormal = cross(In.Normal, In.Tangent);
		normal = normalMap.Sample(Sampler, In.TexCoord);
		//0.0�`1.0�͈̔͂ɂȂ��Ă���^���W�F���g�X�y�[�X�@����
		//-1.0�`1.0�͈̔͂ɕϊ�����B
		normal = (normal * 2.0f) - 1.0f;
		//�@�����^���W�F���g�X�y�[�X����A���[���h�X�y�[�X�ɕϊ�����B
		normal = In.Tangent * normal.x + biNormal * normal.y + In.Normal * normal.z;
	}
	else {
		//�Ȃ��B
		normal = In.Normal;
	}
	
	float3 lig = 0.0f;
	//�|�C���g���C�g���v�Z�B
	float3 ligDir[NUM_POINT_LIGHT];
	for (int i = 0; i < NUM_POINT_LIGHT; i++) {
		ligDir[i] = normalize(In.WorldPos - pointLights.position[i].xyz);

		float distance = length(In.WorldPos - pointLights.position[i].xyz);

		float t = max(0.0f, dot(-ligDir[i], normal));

		float affect = 1.0f - min(1.0f, distance / pointLights.attn[i].x);

		lig += pointLights.color[i] * t * affect;
	}
	//�f�B���N�V�������C�g�̊g�U���ˌ����v�Z����B
	for (int i = 0; i < NUM_DIRECTION_LIGHT; i++) {
		lig += max(0.0f, dot(normal, ligDir[i + 1].xyz * -1.0f)) * dligColor[i];
	}

	//�X�y�L�������C�g�B
	for (int i = 0; i < NUM_DIRECTION_LIGHT; i++) {
		//�����x�N�g�������߂�B
		float3 E = normalize(eyePos[i] - In.WorldPos);
		//���˃x�N�g�������߂�B
		float3 R = -E + 2 * dot(normal, E) * normal;
		//���C�g�̕����ƁA���˃x�N�g���̓��ς����߂�B
		float3 D = dot(-1.0f * ligDir[i + 1].xyz, R);
		float t = max(0.0f, D);
		float specPower = 1.0f;
		if (isHasSpecuraMap == 1) {
			specPower = specularMap.Sample(Sampler, In.TexCoord).r;
		}
		float3 F = pow(t, 2.0f) * pointLights.color[i] * dligColor[i] * specPower *1.0f; //dligColor[i].xyz * pow(t, /*specPow[i]*/specPower.x);
		lig += F;
	}

	if (isShadowReciever == 1) {	//�V���h�E���V�[�o�[�B
									//LVP��Ԃ��猩�����̍ł���O�̐[�x�l���V���h�E�}�b�v����擾����B
		float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
		shadowMapUV *= float2(0.5f, -0.5f);
		shadowMapUV += 0.5f;
		//�V���h�E�}�b�v�͈͓̔����ǂ����𔻒肷��B
		if (shadowMapUV.x < 1.0f
			&& shadowMapUV.x > 0.0f
			&& shadowMapUV.y < 1.0f
			&& shadowMapUV.y > 0.0f
			) {

			///LVP��Ԃł̐[�x�l���v�Z�B
			float zInLVP = In.posInLVP.z / In.posInLVP.w;
			//�V���h�E�}�b�v�ɏ������܂�Ă���[�x�l���擾�B
			float zInShadowMap = g_shadowMap.Sample(Sampler, shadowMapUV);

			if (zInLVP > zInShadowMap + 0.001f) {
				//�e�������Ă���̂ŁA�����キ����
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
/// �V���h�E�}�b�v�����p�̒��_�V�F�[�_�[�B
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
/// �V���h�E�}�b�v�����p�̒��_�V�F�[�_�[�B
/// </summary>
PSInput_ShadowMap VSMain_ShadowMapSkin(VSInputNmTxWeights In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4x4 worldMatrix = 0;
	float4 pos = 0;
	
	//���̒��_�̃��[���h�s����v�Z����B
	float w = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
		//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
		//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
		worldMatrix += boneMatrix[In.Indices[i]] * In.Weights[i];
		w += In.Weights[i];
	}
	//�Ō�̃{�[�����v�Z����B
	worldMatrix += boneMatrix[In.Indices[3]] * (1.0f - w);

	//���_���W�Ɍv�Z�������[���h�s�����Z���āA���_�����[���h��Ԃɕϊ��B
	pos = mul(worldMatrix, In.Position);

	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}
/// <summary>
/// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
/// </summary>
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//�ˉe��Ԃł�Z�l��Ԃ��B
	return In.Position.z / In.Position.w;
}