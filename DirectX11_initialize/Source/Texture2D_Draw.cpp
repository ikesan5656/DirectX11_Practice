#include "Texture2D_Draw.h"
#include"DX11ShaderManager.h"


//���_���\����
struct Vertex
{
	XMFLOAT3 pos;
	XMFLOAT4 col;
	XMFLOAT2 uv;
};

//���_�̍\����
struct SimpleVertex
{
	XMFLOAT3 Pos; //�ʒu
	XMFLOAT2 UV; //�e�N�X�`���[���W
};

#define ALIGN16 _declspec(align(16))
//Simple�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�̃A�v�����\���� �������V�F�[�_�[���̃R���X�^���g�o�b�t�@�[�ƈ�v���Ă���K�v����
struct SIMPLESHADER_CONSTANT_BUFFER
{
	ALIGN16 XMMATRIX mW;
	ALIGN16 float ViewPortWidth;
	ALIGN16 float ViewPortHeight;
};

Texture2D_Draw::Texture2D_Draw()
{

	//�e�N�X�`�����擾
	//texture = TextureManager::GetInstance()->CreateTextureFromFile("")
}

Texture2D_Draw::~Texture2D_Draw()
{

}

void Texture2D_Draw::Init()
{
	//�쐬�����o�[�e�b�N�X�V�F�[�_���擾
	VertexShader = DX11ShaderManager::GetInstance()->CreateVertexShader("2DPipeLine.hlsl", "vsMain");

	//���_�C���v�b�g���C�A�E�g���`	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	InputLayout = DX11ShaderManager::GetInstance()->CreateInputLayout(layout, 2, "Assets/Shaders/2DPipeLine.hlsl", "vsMain");

	//�쐬�����s�N�Z���V�F�[�_���擾
	PixelShader = DX11ShaderManager::GetInstance()->CreatePixelShader("2DPipeLine.hlsl", "psMain");

	//�R���X�^���g�o�b�t�@�[�쐬�@�����ł͕ϊ��s��n���p
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SIMPLESHADER_CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	DirectX11Manager::GetInstance()->GetDevice()->CreateBuffer(&cb, NULL, &m_pConstantBuffer);

	//�o�[�e�b�N�X�o�b�t�@�[�쐬
	//�C�����邱�ƁBz�l���P�ȏ�ɂ��Ȃ��B�N���b�v��Ԃ�z=1�͍ł������Ӗ�����B���������ĕ`�悳��Ȃ��B
	SimpleVertex vertices[] =
	{
		XMFLOAT3(0,100,0),XMFLOAT2(0,1),//���_1,
		XMFLOAT3(100,100,0), XMFLOAT2(0,0),//���_2
		XMFLOAT3(0,200,0),XMFLOAT2(1,1), //���_3
		XMFLOAT3(100,200,0),XMFLOAT2(1,0), //���_4
	};

	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	DirectX11Manager::GetInstance()->GetDevice()->CreateBuffer(&bd, &InitData, &m_pVertexBuffer);

	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	DirectX11Manager::GetInstance()->GetContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//�e�N�X�`���p�T���v���[�쐬
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	DirectX11Manager::GetInstance()->GetDevice()->CreateSamplerState(&SamDesc, &m_pSampler);

	//�e�N�X�`���ǂݍ���
}

void Texture2D_Draw::Uninit()
{

}

void Texture2D_Draw::Update()
{

}

void Texture2D_Draw::Draw()
{

}