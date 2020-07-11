/*!
* @brief	スプライト用のシェーダー。
*/

cbuffer cb : register(b0) {
	float4x4 mvp;		//ワールドビュープロジェクション行列。
	float alpha;		//α値。
};
struct VSInput {
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};
struct PSInput {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);	//カラーテクスチャ。
sampler Sampler : register(s0);

PSInput VSMain(VSInput In)
{
	PSInput psIn;
	psIn.pos = mul(mvp, In.pos);
	psIn.uv = In.uv;
	return psIn;
}
float4 PSMain(PSInput In) : SV_Target0
{
	//テクスチャカラーをそのまま返す。

	float4 color = colorTexture.Sample(Sampler, In.uv);
	color.a *= alpha;
	//モノクロ
	/*float Y = 0.29900 * color.r + 0.58700 * color.b + 0.11400 * color.b;
	color.r = Y;
	color.g = Y;
	color.b = Y;*/
	//コントラストを強める
	//float akarusa = max(color.r, color.g);
	//akarusa = max(akarusa, color.b);
	//if (akarusa > 0.5f) {
	//	//明るさが0.5以上なら、さらに明るくする。
	//	color.r = min(1.0f, color.r * 1.5f);
	//	color.g = min(1.0f, color.g * 1.5f);
	//	color.b = min(1.0f, color.b * 1.5f);
	//}
	//else {
	//	//明るさが0.5未満なら、さらに暗くする。
	//	color.r *= 0.5f;
	//	color.g *= 0.5f;
	//	color.b *= 0.5f;
	//}
	//セピア調
	/*float Y = 0.29900 * color.r + 0.58700 * color.b + 0.11400 * color.b;
	color.r = Y * 1.07f;
	color.g = Y * 0.74f;
	color.b = Y * 0.43f;*/

	return color;
}