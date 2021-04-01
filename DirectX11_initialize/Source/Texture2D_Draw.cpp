#include "Texture2D_Draw.h"
#include"DX11ShaderManager.h"
#include "WindowManager.h"
#include "DirectXTex.h"
#include "WICTextureLoader.h"

//頂点情報構造体
struct Vertex
{
	float x, y, z;
	UINT color;
	float U, V;
};

//頂点の構造体
struct SimpleVertex
{
	XMFLOAT3 Pos; //位置
	XMFLOAT2 UV; //テクスチャー座標
};


Texture2D_Draw::Texture2D_Draw()
{

	//テクスチャを取得
	//texture = TextureManager::GetInstance()->CreateTextureFromFile("")
}

Texture2D_Draw::~Texture2D_Draw()
{

}

void Texture2D_Draw::Init()
{
	//頂点情報定義
	Vertex vertex[4]{
	{ -0.5f, -0.5f, 0.5f, 0xffffffff, 0.0f, 1.0f },
	{ -0.5f, 0.5f, 0.5f, 0xffffffff, 0.0f, 0.0f },
	{ 0.5f, -0.5f, 0.5f, 0xffffffff, 1.0f, 1.0f },
	{ 0.5f, 0.5f, 0.5f, 0xffffffff, 1.0f, 0.0f },
	};

	//頂点バッファー作成
	m_pVertexBuffer = DirectX11Manager::GetInstance()->CreateVertexBuffer(sizeof(vertex), vertex);

	//作成したバーテックスシェーダを取得
	VertexShader = DX11ShaderManager::GetInstance()->CreateVertexShader("Assets/Shaders/test.hlsl", "vsMain");

	//頂点インプットレイアウトを定義	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 4, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	InputLayout = DX11ShaderManager::GetInstance()->CreateInputLayout(layout, 3, "Assets/Shaders/test.hlsl", "vsMain");

	//作成したピクセルシェーダを取得
	PixelShader = DX11ShaderManager::GetInstance()->CreatePixelShader("Assets/Shaders/test.hlsl", "psMain");


	//バーテックスバッファー作成
	//気をつけること。z値を１以上にしない。クリップ空間でz=1は最も奥を意味する。したがって描画されない。
	/*SimpleVertex vertices[] =
	{
		XMFLOAT3(-0.5f, -0.5f, 0.5f),XMFLOAT2(0,1),//頂点1,
		XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT2(0,0),//頂点2
		XMFLOAT3(0.5f, -0.5f, 0.5f),XMFLOAT2(1,1), //頂点3
		XMFLOAT3(0.5f, 0.5f, 0.5f),XMFLOAT2(1,0), //頂点4
	};*/


	
	//テクスチャ用サンプラー作成
	/*D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	DirectX11Manager::GetInstance()->GetDevice()->CreateSamplerState(&SamDesc, &m_pSampler);*/

	m_pSampler = DirectX11Manager::GetInstance()->CreateSampler();

	//テクスチャ読み込み
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

	// viewportの作成
	/*m_Viewport.Width = static_cast<FLOAT>(WindowManager::GetInstance()->GetRC().right - WindowManager::GetInstance()->GetRC().left);
	m_Viewport.Height = static_cast<FLOAT>(WindowManager::GetInstance()->GetRC().bottom - WindowManager::GetInstance()->GetRC().top);
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;
	m_Viewport.TopLeftX = 0;
	m_Viewport.TopLeftY = 0;*/
	//ビューポートセット
	//DirectX11Manager::GetInstance()->GetContext()->RSSetViewports(1, &m_Viewport);

	//使用するシェーダのセット
	DX11ShaderManager::GetInstance()->SetVertexShader(VertexShader);
	DX11ShaderManager::GetInstance()->SetPixelShader(PixelShader);

	//テクスチャをシェーダに渡す
	DirectX11Manager::GetInstance()->GetContext()->PSSetShaderResources(0, 1, &m_pTexture);
	DirectX11Manager::GetInstance()->GetContext()->PSSetSamplers(0, 1, &m_pSampler);

	//頂点インプットレイアウトをセット
	DirectX11Manager::GetInstance()->GetContext()->IASetInputLayout(InputLayout);

	//プリミティブ・トポロジーをセット
	DirectX11Manager::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	//頂点バッファをセット
	DirectX11Manager::GetInstance()->SetVertexBuffer(m_pVertexBuffer, sizeof(Vertex));

	//プリミティブをレンダリング
	DirectX11Manager::GetInstance()->GetContext()->Draw(4, 0);
}