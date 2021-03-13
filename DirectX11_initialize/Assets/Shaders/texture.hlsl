/*���_�V�F�[�_�[&�s�N�Z���V�F�[�_�[*/
Texture2D g_texture : register(t0);
SamplerState samLinear : register(s0);


//���_�V�F�[�_�[���͒�`
struct VS_INPUT
{
	//���W
	float3 Pos : POSITION;
	//�F
	float4 Col : COLOR;
	//UV
	float2 Tex : TEXCOORD;
};

//�s�N�Z���V�F�[�_�[���͒�`
struct PS_INPUT
{
	//���W
	float4 Pos : SV_POSITION;
	//�F
	float4 Col : COLOR;
	//UV
	float2 Tex : TEXCOORD;
};

//���_�V�F�[�_�֐�
PS_INPUT vsMain(VS_INPUT pos)
{
	PS_INPUT o = (PS_INPUT)0;
	o.Pos = float4(pos.Pos, 1);
	o.Col = pos.Col;
	o.Tex = pos.Tex;
	return o;
}

//�s�N�Z���V�F�[�_�[�֐�
float4 psMain(PS_INPUT input) : SV_TARGET
{
	float4 result = 0;
	result = g_texture.Sample(samLinear, input.uv)
	return result;
}