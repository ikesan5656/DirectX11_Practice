#include "DirectX11Manager.h"
#include "WindowManager.h"
#include <locale.h>
#include"DirectXTex.h"
#include <iostream>
DirectX::TexMetadata metadata;
DirectX::ScratchImage image;

DirectX11Manager::DirectX11Manager()
{

}

DirectX11Manager::~DirectX11Manager()
{

}

//========================================================
//ハードウェアチェック
//*H複数GPUがあった場合最適なものを使用するため
//=========================================================
HRESULT DirectX11Manager::HardwareCheck()
{
	//IDXGIFactory* factory;
	//IDXGIAdapter* adapter;
	//IDXGIOutput* adapterOutput;
	unsigned int numModes = 0;
	size_t stringLength;
	DXGI_ADAPTER_DESC adapterDesc;


	//グラフィック・インターフェース・ファクトリを作成
	auto hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)& factory);

	if (FAILED(hr))
	{

		return hr;
	}

	int GPUNumber = 0;
	int GPUMaxMem = 0;

	//GPUの中で一番メモリ量の多いアダプターを検索
	for (int i = 0; i < 100; i++)
	{
		IDXGIAdapter* add;
		hr = factory->EnumAdapters(i, &add);
		if (FAILED(hr))
			break;
		hr = add->GetDesc(&adapterDesc);

		char videoCardDescription[128];
		//ビデオカード名を取得
		int error = wcstombs_s(&stringLength, videoCardDescription, 128, adapterDesc.Description, 128);
		if (error != 0)
		{
			break;
		}
		//cout << "ビデオカード名 : " << videoCardDescription << endl;

		//ビデオカードメモリを取得（MB単位）
		int videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
		//cout << "ビデオメモリー : " << videoCardMemory << endl;

		//アウトプット（モニター）に番号IDを付ける
		hr = add->EnumOutputs(0, &adapterOutput);
		if (FAILED(hr))
		{
			continue;
		}

		//DXGI_FORMAT_R8G8B8A8_UNORM の表示形式数を取得する
		hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
		if (FAILED(hr))
		{
			continue;
		}
		//cout << "RBGA8_UNORM Count : " << numModes << endl;

		if (videoCardMemory > GPUMaxMem)
		{
			GPUMaxMem = videoCardMemory;
			GPUNumber = i;
		}
		add->Release();
		//アダプタアウトプットを解放
		adapterOutput->Release();
		adapterOutput = 0;
	}

	//グラフィック インタフェース アダプターを作成
	hr = factory->EnumAdapters(GPUNumber, &adapter);
	if (FAILED(hr))
	{
		return hr;
	}

	return hr;

}

//========================================================
//スワップチェインとデバイス作成
//*
//=========================================================
HRESULT DirectX11Manager::CreateDeviceAndSwapChain(HWND hWnd)
{
	UINT cdev_flags = 0;
	#ifdef _DEBUG
		//開放忘れ検知
		cdev_flags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

	// スワップチェイン設定
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = (LONG)SCREEN_WIDTH;
	sd.BufferDesc.Height = (LONG)SCREEN_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 1000;
	sd.BufferDesc.RefreshRate.Denominator = 1;  //1/60 = 60fps
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
	};

	// DirectX11デバイスとスワップチェイン作成
	auto hr = D3D11CreateDeviceAndSwapChain(adapter, D3D_DRIVER_TYPE_UNKNOWN, NULL,
		cdev_flags, featureLevels, 1, D3D11_SDK_VERSION, &sd,
		&m_pSwapChain, &m_pDevice, NULL, &m_pImContext);

	if (FAILED(hr)) {
		
		return hr;
	}

	//アダプタを解放
	adapter->Release();
	adapter = 0;

	//ファクトリを解放
	factory->Release();
	factory = 0;


	return hr;
}

//========================================================
//DirectX11の初期化
//*HRESULTはエラーチェックのため
//=========================================================
HRESULT DirectX11Manager::Init(HWND hWnd)
{
	HRESULT hr;
	//*引数でウィンドウハンドルを渡している

	//ハードウェアのチェック
	HardwareCheck();

	//スワップチェインとデバイスの作成
	CreateDeviceAndSwapChain(hWnd);

	//バックバッファーテクスチャーを取得（既にあるので作成ではない
	ID3D11Texture2D *pBackBuffer_Tex;

	// スワップチェインに用意されたバッファ（2Dテクスチャ）を取得
	hr = m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer_Tex));
	if (FAILED(hr)) {
		return hr;
	}

	// レンダーターゲットView作成
	hr = m_pDevice->CreateRenderTargetView(pBackBuffer_Tex, NULL, &m_pRTView);
	if (FAILED(hr)) {
		return hr;
	}

	if (pBackBuffer_Tex) {
		pBackBuffer_Tex->Release();
		pBackBuffer_Tex = nullptr;
	}

	//深度ステンシルバッファ作成(１回行えばOK)
	D3D11_TEXTURE2D_DESC txDesc;
	ZeroMemory(&txDesc, sizeof(txDesc));
	txDesc.Width = SCREEN_WIDTH;
	txDesc.Height = SCREEN_HEIGHT;
	txDesc.MipLevels = 1;
	txDesc.ArraySize = 1;
	txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	txDesc.SampleDesc.Count = 1;
	txDesc.SampleDesc.Quality = 0;
	txDesc.Usage = D3D11_USAGE_DEFAULT;
	txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	txDesc.CPUAccessFlags = 0;
	txDesc.MiscFlags = 0;
	hr = m_pDevice->CreateTexture2D(&txDesc, NULL, &m_pDepthStencilTexture);
	if (FAILED(hr))
		return hr;

	//深度ステンシルビューを作成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.Format = txDesc.Format;
	dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsDesc.Texture2D.MipSlice = 0;
	hr = m_pDevice->CreateDepthStencilView(m_pDepthStencilTexture, &dsDesc, &m_pDepthStencilView);
	if (FAILED(hr))
		return hr;

	//ビューポート設定
	m_Viewport.Width = static_cast<FLOAT>(WindowManager::GetInstance()->GetRC().right - WindowManager::GetInstance()->GetRC().left);
	m_Viewport.Height = static_cast<FLOAT>(WindowManager::GetInstance()->GetRC().bottom - WindowManager::GetInstance()->GetRC().top);
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;
	m_Viewport.TopLeftX = 0;
	m_Viewport.TopLeftY = 0;

	//デプスステンシルビュー用のテクスチャーを作成
	/*D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = SCREEN_WIDTH;
	descDepth.Height = SCREEN_HEIGHT;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	m_pDevice->CreateTexture2D(&descDepth, NULL, &m_pBackBuffer_DSTex);
	//そのテクスチャーに対しデプスステンシルビュー(DSV)を作成
	m_pDevice->CreateDepthStencilView(m_pBackBuffer_DSTex, NULL, &m_pBackBuffer_DSTexDSV);//正しい動作


	//レンダーターゲットビューと深度ステンシルビューをパイプラインにバインド
	m_pImContext->OMSetRenderTargets(1, &m_pRTView, m_pBackBuffer_DSTexDSV);*/

	// viewportの作成
	//m_Viewport.Width = static_cast<FLOAT>(WindowManager::GetInstance()->GetRC().right - WindowManager::GetInstance()->GetRC().left);
	//m_Viewport.Height = static_cast<FLOAT>(WindowManager::GetInstance()->GetRC().bottom - WindowManager::GetInstance()->GetRC().top);
	//m_Viewport.MinDepth = 0.0f;
	//m_Viewport.MaxDepth = 1.0f;
	//m_Viewport.TopLeftX = 0;
	//m_Viewport.TopLeftY = 0;
	////ビューポートセット
	//m_pImContext->RSSetViewports(1, &m_Viewport);

	//ラスタライザーの定義D3D11_FILL_WIREFRAME,
	
	D3D11_RASTERIZER_DESC hRasterizerDesc = {
			D3D11_FILL_SOLID,
			D3D11_CULL_BACK,	//ポリゴンの裏面を消す
			FALSE,
			0,
			0.0f,
			FALSE,
			FALSE,
			FALSE,
			FALSE,
			FALSE
	};

	ID3D11RasterizerState* hpRasterizerState = NULL;

	//ラスタライザーの作成
	//カリングモードやフィルモードを変更出来る
	/*if (FAILED(m_pDevice->CreateRasterizerState(&hRasterizerDesc, &hpRasterizerState))) {
		MessageBox(hWnd, _T("CreateRasterizerState"), _T("Err"), MB_ICONSTOP);
		//goto End;
	}*/

	m_pDevice->CreateRasterizerState(&hRasterizerDesc, &hpRasterizerState);
	//ラスタライザーをコンテキストに設定
	m_pImContext->RSSetState(hpRasterizerState);

	hpRasterizerState->Release();
	hpRasterizerState = nullptr;

	return hr;
}

//開放処理
void DirectX11Manager::AllRelease()
{
	//スワップチェイン開放
	//m_pSwapChain->Release();
	//m_pImContext->Release();
	//m_pDevice->Release();
	//SafeRelease(m_pSwapChain);
	//SafeRelease(m_pDeviceContext);
	//SafeRelease(m_pSwapChain);

	if (m_pRTView) {
		m_pRTView->Release();
		m_pRTView = nullptr;
	}

	if (m_pDepthStencilTexture) {
		m_pDepthStencilTexture->Release();
		m_pDepthStencilTexture = nullptr;
	}

	if (m_pDepthStencilView) {
		m_pDepthStencilView->Release();
		m_pDepthStencilView = nullptr;
	}
	/*if (m_pBackBuffer_DSTex) {
		m_pBackBuffer_DSTex->Release();
		m_pBackBuffer_DSTex = nullptr;
	}

	if (m_pBackBuffer_DSTexDSV) {
		m_pBackBuffer_DSTexDSV->Release();
		m_pBackBuffer_DSTexDSV = nullptr;
	}*/
	/*if (m_pRTTex) {
		m_pRTTex->Release();
		m_pRTTex = nullptr;
	}*/

	/*シェーダー関連開放*/

	if (m_pImContext) {
		m_pImContext->Release();
		m_pImContext = nullptr;
	}

	if (m_pSwapChain) {
		m_pSwapChain->Release();
		m_pSwapChain = nullptr;
	}



	if (m_pDevice) {
		m_pDevice->Release();
		m_pDevice = nullptr;
	}



	
}

//シングルトンインスタンスの取得
DirectX11Manager * DirectX11Manager::GetInstance()
{
	static DirectX11Manager self;
	//自身を返す
	return &self;
}

//デバイスの取得
ID3D11Device * DirectX11Manager::GetDevice()
{
	return m_pDevice;
}

//コンテキストの取得
ID3D11DeviceContext * DirectX11Manager::GetContext()
{
	return m_pImContext;
}

//ビューポートの取得
D3D11_VIEWPORT DirectX11Manager::GetViewport()
{
	return m_Viewport;
}

ID3D11Buffer * DirectX11Manager::CreateIndexBuffer(WORD* Index, UINT IndexNum)
{
	//インデックスバッファ作成
	D3D11_BUFFER_DESC hBufferDesc;
	ZeroMemory(&hBufferDesc, sizeof(hBufferDesc));
	hBufferDesc.ByteWidth = sizeof(WORD) * IndexNum;
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA hSubResourceData;
	ZeroMemory(&hSubResourceData, sizeof(hSubResourceData));
	hSubResourceData.pSysMem = Index;

	ID3D11Buffer* hpBuffer;
	if (FAILED(m_pDevice->CreateBuffer(&hBufferDesc, &hSubResourceData, &hpBuffer))) {
		return nullptr;
	}
	return hpBuffer;
}

ID3D11Buffer* DirectX11Manager::CreateCubeIndexBuffer(WORD* Index)
{
	//インデックスバッファ作成
	D3D11_BUFFER_DESC hBufferDesc;
	ZeroMemory(&hBufferDesc, sizeof(hBufferDesc));
	hBufferDesc.ByteWidth = sizeof(WORD) * 6 * 6;
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA hSubResourceData;
	ZeroMemory(&hSubResourceData, sizeof(hSubResourceData));
	hSubResourceData.pSysMem = Index;

	ID3D11Buffer* hpBuffer;
	if (FAILED(m_pDevice->CreateBuffer(&hBufferDesc, &hSubResourceData, &hpBuffer))) {
		return nullptr;
	}
	return hpBuffer;
}



void DirectX11Manager::SetVertexBuffer(ID3D11Buffer * VertexBuffer, UINT VertexSize)
{
	UINT hOffsets = 0;
	m_pImContext->IASetVertexBuffers(0, 1, &VertexBuffer, &VertexSize, &hOffsets);
}

void DirectX11Manager::SetIndexBuffer(ID3D11Buffer * IndexBuffer)
{
	m_pImContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void DirectX11Manager::SetTexture2D(UINT RegisterNo, ID3D11ShaderResourceView * Texture)
{
	m_pImContext->PSSetShaderResources(RegisterNo, 1, &Texture);
}

ID3D11SamplerState* DirectX11Manager::CreateSampler()
{
	//テクスチャ用サンプラー作成
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	SamDesc.MinLOD = 0;
	SamDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* pSampler;
	m_pDevice->CreateSamplerState(&SamDesc, &pSampler);

	return pSampler;

}

ID3D11ShaderResourceView * DirectX11Manager::CreateTextureFromFile(const char * filename)
{
	const char* pExtension = "";
	for (size_t i = strlen(filename); i == 0; i--)
	{
		if (filename[i - 1] == '.')
		{
			pExtension = &filename[i];
		}
	}

	WCHAR path[256];
	size_t len = 0;
	mbstowcs_s(&len, path, 256, filename, _TRUNCATE);

	TexMetadata metadata;
	ScratchImage image;

	if (strcmp(pExtension, "dds") == 0)
	{
		LoadFromDDSFile(path, DDS_FLAGS::DDS_FLAGS_NONE, &metadata, image);
	}
	else if (strcmp(pExtension, "tga") == 0)
	{
		LoadFromTGAFile(path, &metadata, image);
	}
	else
	{
		LoadFromWICFile(path, WIC_FLAGS::WIC_FLAGS_NONE, &metadata, image);
	}



	ID3D11ShaderResourceView * pView;
	// 画像からシェーダリソースViewの作成
	CreateShaderResourceView(m_pDevice, image.GetImages(), image.GetImageCount(), metadata, &pView);


	//m_Format = metadata.format;
	//m_Width = static_cast<UINT>(metadata.width);
	//m_Height = static_cast<UINT>(metadata.height);
	//m_pShaderResourceView.Swap(pView);
	return pView;
}

void DirectX11Manager::DrawBegin()
{
	/*-- 指定色で画面クリア ----------------------------------------------------*/

	//画面色設定
	float ClearColor[4] = { 0.89f, 0.97f, 1.0f, 1.0f }; //red,green,blue,alpha
	//レンダーターゲットのすべての要素を1つの値に設定
	m_pImContext->ClearRenderTargetView(m_pRTView, ClearColor);
	//ビューポートの配列をパイプラインのラスタライザーステージにバインドする
	//m_pImContext->RSSetViewports(1, &m_Viewport);

	/*--------------------------------------------------------------------------*/

	//ビューポート設定
	m_pImContext->RSSetViewports(1, &m_Viewport);

	//RenderTargetをバックバッファ
	//ID3D11RenderTargetView* rtv[1] = { m_pRTView };
	m_pImContext->OMSetRenderTargets(1, &m_pRTView, nullptr);


	//デプスステンシルビューをクリア
	m_pImContext->ClearDepthStencilView(m_pDepthStencilView,D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

}

void DirectX11Manager::DrawEnd()
{
	m_pSwapChain->Present(1, 0);
}

void DirectX11Manager::DrawIndexed(UINT VertexNum)
{
	m_pImContext->DrawIndexed(VertexNum, 0, 0);
}









