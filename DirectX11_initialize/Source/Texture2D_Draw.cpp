#include "Texture2D_Draw.h"
#include"DX11ShaderManager.h"
#include "WindowManager.h"
#include "DirectXTex.h"
#include "WICTextureLoader.h"

//頂点情報構造体
struct Vertex
{
	XMFLOAT3 pos;
	XMFLOAT4 col;
	XMFLOAT2 uv;
};

//頂点の構造体
struct SimpleVertex
{
	XMFLOAT3 Pos; //位置
	XMFLOAT2 UV; //テクスチャー座標
};

#define ALIGN16 _declspec(align(16))
//Simpleシェーダー用のコンスタントバッファーのアプリ側構造体 もちろんシェーダー内のコンスタントバッファーと一致している必要あり
struct SIMPLESHADER_CONSTANT_BUFFER
{
	ALIGN16 XMMATRIX mW;
	ALIGN16 float ViewPortWidth;
	ALIGN16 float ViewPortHeight;
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
	//作成したバーテックスシェーダを取得
	VertexShader = DX11ShaderManager::GetInstance()->CreateVertexShader("Assets/Shaders/test.hlsl", "vsMain");

	//頂点インプットレイアウトを定義	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	InputLayout = DX11ShaderManager::GetInstance()->CreateInputLayout(layout, 2, "Assets/Shaders/test.hlsl", "vsMain");

	//作成したピクセルシェーダを取得
	PixelShader = DX11ShaderManager::GetInstance()->CreatePixelShader("Assets/Shaders/test.hlsl", "psMain");

	//コンスタントバッファー作成　ここでは変換行列渡し用
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SIMPLESHADER_CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	DirectX11Manager::GetInstance()->GetDevice()->CreateBuffer(&cb, NULL, &m_pConstantBuffer);

	//バーテックスバッファー作成
	//気をつけること。z値を１以上にしない。クリップ空間でz=1は最も奥を意味する。したがって描画されない。
	SimpleVertex vertices[] =
	{
		XMFLOAT3(0,100,0),XMFLOAT2(0,1),//頂点1,
		XMFLOAT3(100,100,0), XMFLOAT2(0,0),//頂点2
		XMFLOAT3(0,200,0),XMFLOAT2(1,1), //頂点3
		XMFLOAT3(100,200,0),XMFLOAT2(1,0), //頂点4
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

	//バーテックスバッファーをセット
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	DirectX11Manager::GetInstance()->GetContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//テクスチャ用サンプラー作成
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	DirectX11Manager::GetInstance()->GetDevice()->CreateSamplerState(&SamDesc, &m_pSampler);

	//テクスチャ読み込み
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
	//ワールドトランスフォーム
	float x = 0;
	x += 0.01;
	XMMATRIX Tran;
	Tran = DirectX::XMMatrixTranslation(x, 0, 0);
	World = Tran;

	//使用するシェーダのセット
	DX11ShaderManager::GetInstance()->SetVertexShader(VertexShader);
	DX11ShaderManager::GetInstance()->SetPixelShader(PixelShader);

	//シェーダーのコンスタントバッファーに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData;
	SIMPLESHADER_CONSTANT_BUFFER cb;
	if (SUCCEEDED(DirectX11Manager::GetInstance()->GetContext()->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//ワールド行列を渡す
		cb.mW = World;
		cb.mW = DirectX::XMMatrixTranspose(World);
		//ビューポートサイズを渡す（クライアント領域の横と縦）
		cb.ViewPortWidth = SCREEN_WIDTH;
		cb.ViewPortHeight = SCREEN_HEIGHT;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		DirectX11Manager::GetInstance()->GetContext()->Unmap(m_pConstantBuffer, 0);
	}

	//コンスタントバッファー
	DirectX11Manager::GetInstance()->GetContext()->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	DirectX11Manager::GetInstance()->GetContext()->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	//頂点インプットレイアウトをセット
	DirectX11Manager::GetInstance()->GetContext()->IASetInputLayout(InputLayout);
	//プリミティブ・トポロジーをセット
	DirectX11Manager::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//テクスチャをシェーダに渡す
	DirectX11Manager::GetInstance()->GetContext()->PSSetSamplers(0, 1, &m_pSampler);
	DirectX11Manager::GetInstance()->GetContext()->PSSetShaderResources(0, 1, &m_pTexture);

	//プリミティブをレンダリング
	DirectX11Manager::GetInstance()->GetContext()->Draw(4, 0);
}