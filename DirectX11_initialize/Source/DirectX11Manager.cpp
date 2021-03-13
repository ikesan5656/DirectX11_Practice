#include "DirectX11Manager.h"
#include "WindowManager.h"


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
	//*引数でウィンドウハンドルを渡している

	//ハードウェアのチェック
	HardwareCheck();

	//スワップチェインとデバイスの作成
	CreateDeviceAndSwapChain(hWnd);

	//バックバッファーテクスチャーを取得（既にあるので作成ではない
	ID3D11Texture2D *pBackBuffer_Tex;

	// スワップチェインに用意されたバッファ（2Dテクスチャ）を取得
	auto hr = m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer_Tex));
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

	//デプスステンシルビュー用のテクスチャーを作成
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = 1280;
	descDepth.Height = 720;
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
	m_pDevice->CreateDepthStencilView(m_pBackBuffer_DSTex, NULL, &m_pBackBuffer_DSTexDSV);

	//レンダーターゲットビューと深度ステンシルビューをパイプラインにバインド
	m_pImContext->OMSetRenderTargets(1, &m_pRTView, m_pBackBuffer_DSTexDSV);

	// viewportの作成
	m_Viewport.Width = static_cast<FLOAT>(WindowManager::GetInstance()->GetRC().right - WindowManager::GetInstance()->GetRC().left);
	m_Viewport.Height = static_cast<FLOAT>(WindowManager::GetInstance()->GetRC().bottom - WindowManager::GetInstance()->GetRC().top);
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;
	m_Viewport.TopLeftX = 0;
	m_Viewport.TopLeftY = 0;
	//ビューポートセット
	m_pImContext->RSSetViewports(1, &m_Viewport);

	//ラスタライザーの定義
	
	D3D11_RASTERIZER_DESC hRasterizerDesc = {
			D3D11_FILL_SOLID,
			D3D11_CULL_FRONT,	//ポリゴンを前から見る
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
	if (FAILED(m_pDevice->CreateRasterizerState(&hRasterizerDesc, &hpRasterizerState))) {
	/*	MessageBox(hWnd, _T("CreateRasterizerState"), _T("Err"), MB_ICONSTOP);
		goto End;*/
	}

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
	if (m_pBackBuffer_DSTex) {
		m_pBackBuffer_DSTex->Release();
		m_pBackBuffer_DSTex = nullptr;
	}

	if (m_pBackBuffer_DSTexDSV) {
		m_pBackBuffer_DSTexDSV->Release();
		m_pBackBuffer_DSTexDSV = nullptr;
	}
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

ID3D11Buffer * DirectX11Manager::CreateIndexBuffer(UINT * Index, UINT IndexNum)
{
	//インデックスバッファ作成
	D3D11_BUFFER_DESC hBufferDesc;
	ZeroMemory(&hBufferDesc, sizeof(hBufferDesc));
	hBufferDesc.ByteWidth = sizeof(UINT) * IndexNum;
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

void DirectX11Manager::DrawBegin()
{
	/*-- 指定色で画面クリア ----------------------------------------------------*/

	//画面色設定
	float ClearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //red,green,blue,alpha
	//レンダーターゲットのすべての要素を1つの値に設定
	m_pImContext->ClearRenderTargetView(m_pRTView, ClearColor);
	//ビューポートの配列をパイプラインのラスタライザーステージにバインドする
	//m_pImContext->RSSetViewports(1, &m_Viewport);

	/*--------------------------------------------------------------------------*/

	//RenderTargetをバックバッファ
	ID3D11RenderTargetView* rtv[1] = { m_pRTView };
	m_pImContext->OMSetRenderTargets(1, rtv, nullptr);
}

void DirectX11Manager::DrawEnd()
{
	m_pSwapChain->Present(0, 0);
}

void DirectX11Manager::DrawIndexed(UINT VertexNum)
{
	m_pImContext->DrawIndexed(VertexNum, 0, 0);
}









