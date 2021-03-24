#include "Texture2D_Draw.h"
#include"DX11ShaderManager.h"
#include "WindowManager.h"
#include "DirectXTex.h"
#include "WICTextureLoader.h"

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
	VertexShader = DX11ShaderManager::GetInstance()->CreateVertexShader("Assets/Shaders/test.hlsl", "vsMain");

	//���_�C���v�b�g���C�A�E�g���`	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	InputLayout = DX11ShaderManager::GetInstance()->CreateInputLayout(layout, 2, "Assets/Shaders/test.hlsl", "vsMain");

	//�쐬�����s�N�Z���V�F�[�_���擾
	PixelShader = DX11ShaderManager::GetInstance()->CreatePixelShader("Assets/Shaders/test.hlsl", "psMain");

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
	m_pTexture = DirectX11Manager::GetInstance()->CreateTextureFromFile(L"Assets/Textures/WoodenBox_simple.jpg");
	//CreateWICTextureFromFile(DirectX11Manager::GetInstance()->GetDevice(), (L"sample.png"), &m_pTexture, &m_pTextureView);
	//CreateWICTextureFromFile()
}

void Texture2D_Draw::Uninit()
{
	if (VertexShader) {
		VertexShader->Release();
		VertexShader = nullptr;
	}
	if (PixelShader) {
		PixelShader->Release();
		PixelShader = nullptr;
	}
	if (InputLayout) {
		InputLayout->Release();
		InputLayout = nullptr;
	}
	if (m_pConstantBuffer) {
		m_pConstantBuffer->Release();
		m_pConstantBuffer = nullptr;
	}

	if (m_pVertexBuffer) {
		m_pVertexBuffer->Release();
		m_pVertexBuffer = nullptr;
	}

	if (m_pSampler) {
		m_pSampler->Release();
		m_pSampler = nullptr;
	}

	if (m_pTexture) {
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	
}

void Texture2D_Draw::Update()
{

}

void Texture2D_Draw::Draw()
{
	XMMATRIX World;
	//���[���h�g�����X�t�H�[��
	float x = 0;
	x += 0.01;
	XMMATRIX Tran;
	Tran = DirectX::XMMatrixTranslation(x, 0, 0);
	World = Tran;

	//�g�p����V�F�[�_�̃Z�b�g
	DX11ShaderManager::GetInstance()->SetVertexShader(VertexShader);
	DX11ShaderManager::GetInstance()->SetPixelShader(PixelShader);

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	SIMPLESHADER_CONSTANT_BUFFER cb;
	if (SUCCEEDED(DirectX11Manager::GetInstance()->GetContext()->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�s���n��
		cb.mW = World;
		cb.mW = DirectX::XMMatrixTranspose(World);
		//�r���[�|�[�g�T�C�Y��n���i�N���C�A���g�̈�̉��Əc�j
		cb.ViewPortWidth = SCREEN_WIDTH;
		cb.ViewPortHeight = SCREEN_HEIGHT;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		DirectX11Manager::GetInstance()->GetContext()->Unmap(m_pConstantBuffer, 0);
	}

	//�R���X�^���g�o�b�t�@�[
	DirectX11Manager::GetInstance()->GetContext()->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	DirectX11Manager::GetInstance()->GetContext()->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	DirectX11Manager::GetInstance()->GetContext()->IASetInputLayout(InputLayout);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	DirectX11Manager::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//�e�N�X�`�����V�F�[�_�ɓn��
	DirectX11Manager::GetInstance()->GetContext()->PSSetSamplers(0, 1, &m_pSampler);
	DirectX11Manager::GetInstance()->GetContext()->PSSetShaderResources(0, 1, &m_pTexture);

	//�v���~�e�B�u�������_�����O
	DirectX11Manager::GetInstance()->GetContext()->Draw(4, 0);
}