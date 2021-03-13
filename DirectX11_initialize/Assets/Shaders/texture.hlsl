/*頂点シェーダー&ピクセルシェーダー*/
Texture2D g_texture : register(t0);
SamplerState samLinear : register(s0);


//頂点シェーダー入力定義
struct VS_INPUT
{
	//座標
	float3 Pos : POSITION;
	//色
	float4 Col : COLOR;
	//UV
	float2 Tex : TEXCOORD;
};

//ピクセルシェーダー入力定義
struct PS_INPUT
{
	//座標
	float4 Pos : SV_POSITION;
	//色
	float4 Col : COLOR;
	//UV
	float2 Tex : TEXCOORD;
};

//頂点シェーダ関数
PS_INPUT vsMain(VS_INPUT pos)
{
	PS_INPUT o = (PS_INPUT)0;
	o.Pos = float4(pos.Pos, 1);
	o.Col = pos.Col;
	o.Tex = pos.Tex;
	return o;
}

//ピクセルシェーダー関数
float4 psMain(PS_INPUT input) : SV_TARGET
{
	float4 result = 0;
	result = g_texture.Sample(samLinear, input.uv)
	return result;
}