/*頂点シェーダー&ピクセルシェーダー*/

//頂点シェーダー入力定義
struct VS_INPUT
{
	//座標
	float3 Pos : POSITION;
	//色
	float4 Col : TEXCOORD;
};

//ピクセルシェーダー入力定義
struct PS_INPUT
{
	//座標
	float4 Pos : SV_POSITION;
	//色
	float4 Col : TEXCOORD;
};

//頂点シェーダ関数
PS_INPUT vsMain(VS_INPUT pos)
{
	PS_INPUT o = (PS_INPUT)0;
	o.Pos = float4(pos.Pos, 1);
	o.Col = pos.Col;
	return o;
}

//ピクセルシェーダー関数
float4 psMain(PS_INPUT input) : SV_TARGET
{
	return input.Col;
}