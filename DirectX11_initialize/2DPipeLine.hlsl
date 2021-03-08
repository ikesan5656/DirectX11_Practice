/*���_�V�F�[�_�[&�s�N�Z���V�F�[�_�[*/

//���_�V�F�[�_�[���͒�`
struct VS_INPUT
{
	//���W
	float3 Pos : POSITION;
	//�F
	float4 Col : TEXCOORD;
};

//�s�N�Z���V�F�[�_�[���͒�`
struct PS_INPUT
{
	//���W
	float4 Pos : SV_POSITION;
	//�F
	float4 Col : TEXCOORD;
};

//���_�V�F�[�_�֐�
PS_INPUT vsMain(VS_INPUT pos)
{
	PS_INPUT o = (PS_INPUT)0;
	o.Pos = float4(pos.Pos, 1);
	o.Col = pos.Col;
	return o;
}

//�s�N�Z���V�F�[�_�[�֐�
float4 psMain(PS_INPUT input) : SV_TARGET
{
	return input.Col;
}