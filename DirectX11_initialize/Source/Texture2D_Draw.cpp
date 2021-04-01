#include "Texture2D_Draw.h"
#include"DX11ShaderManager.h"
#include "WindowManager.h"
#include "DirectXTex.h"
#include "WICTextureLoader.h"

//���_���\����
struct Vertex
{
	float x, y, z;
	UINT color;
	float U, V;
};

//���_�̍\����
struct SimpleVertex
{
	XMFLOAT3 Pos; //�ʒu
	XMFLOAT2 UV; //�e�N�X�`���[���W
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
	//���_����`
	Vertex vertex[4]{
	{ -0.5f, -0.5f, 0.5f, 0xffffffff, 0.0f, 1.0f },
	{ -0.5f, 0.5f, 0.5f, 0xffffffff, 0.0f, 0.0f },
	{ 0.5f, -0.5f, 0.5f, 0xffffffff, 1.0f, 1.0f },
	{ 0.5f, 0.5f, 0.5f, 0xffffffff, 1.0f, 0.0f },
	};

	//���_�o�b�t�@�[�쐬
	m_pVertexBuffer = DirectX11Manager::GetInstance()->CreateVertexBuffer(sizeof(vertex), vertex);

	//�쐬�����o�[�e�b�N�X�V�F�[�_���擾
	VertexShader = DX11ShaderManager::GetInstance()->CreateVertexShader("Assets/Shaders/test.hlsl", "vsMain");

	//���_�C���v�b�g���C�A�E�g���`	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 4, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	InputLayout = DX11ShaderManager::GetInstance()->CreateInputLayout(layout, 3, "Assets/Shaders/test.hlsl", "vsMain");

	//�쐬�����s�N�Z���V�F�[�_���擾
	PixelShader = DX11ShaderManager::GetInstance()->CreatePixelShader("Assets/Shaders/test.hlsl", "psMain");


	//�o�[�e�b�N�X�o�b�t�@�[�쐬
	//�C�����邱�ƁBz�l���P�ȏ�ɂ��Ȃ��B�N���b�v��Ԃ�z=1�͍ł������Ӗ�����B���������ĕ`�悳��Ȃ��B
	/*SimpleVertex vertices[] =
	{
		XMFLOAT3(-0.5f, -0.5f, 0.5f),XMFLOAT2(0,1),//���_1,
		XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT2(0,0),//���_2
		XMFLOAT3(0.5f, -0.5f, 0.5f),XMFLOAT2(1,1), //���_3
		XMFLOAT3(0.5f, 0.5f, 0.5f),XMFLOAT2(1,0), //���_4
	};*/


	
	//�e�N�X�`���p�T���v���[�쐬
	/*D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	DirectX11Manager::GetInstance()->GetDevice()->CreateSamplerState(&SamDesc, &m_pSampler);*/

	m_pSampler = DirectX11Manager::GetInstance()->CreateSampler();

	//�e�N�X�`���ǂݍ���
	m_pTexture = DirectX11Manager::GetInstance()->CreateTextureFromFile("Assets/Textures/WoodenBox_simple.jpg");
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

	// viewport�̍쐬
	/*m_Viewport.Width = static_cast<FLOAT>(WindowManager::GetInstance()->GetRC().right - WindowManager::GetInstance()->GetRC().left);
	m_Viewport.Height = static_cast<FLOAT>(WindowManager::GetInstance()->GetRC().bottom - WindowManager::GetInstance()->GetRC().top);
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;
	m_Viewport.TopLeftX = 0;
	m_Viewport.TopLeftY = 0;*/
	//�r���[�|�[�g�Z�b�g
	//DirectX11Manager::GetInstance()->GetContext()->RSSetViewports(1, &m_Viewport);

	//�g�p����V�F�[�_�̃Z�b�g
	DX11ShaderManager::GetInstance()->SetVertexShader(VertexShader);
	DX11ShaderManager::GetInstance()->SetPixelShader(PixelShader);

	//�e�N�X�`�����V�F�[�_�ɓn��
	DirectX11Manager::GetInstance()->GetContext()->PSSetShaderResources(0, 1, &m_pTexture);
	DirectX11Manager::GetInstance()->GetContext()->PSSetSamplers(0, 1, &m_pSampler);

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	DirectX11Manager::GetInstance()->GetContext()->IASetInputLayout(InputLayout);

	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	DirectX11Manager::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	//���_�o�b�t�@���Z�b�g
	DirectX11Manager::GetInstance()->SetVertexBuffer(m_pVertexBuffer, sizeof(Vertex));

	//�v���~�e�B�u�������_�����O
	DirectX11Manager::GetInstance()->GetContext()->Draw(4, 0);
}