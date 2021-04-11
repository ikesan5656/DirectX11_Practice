#pragma once
/*DirectX11のライブラリを管理するクラス
シングルトンクラスとして利用
*/

//WindowsApplicationを使用するので必須
//#include <windows.h>
//DirectX11のAPI
#include <d3d11.h>
////シェーダーのコンパイラ
//#include <d3dcompiler.h>
//ベクトルやFLOAT3など便利な算術ライブラリ(必須ではない)
#include <DirectXMath.h>
//デバイスの管理をしやすくするためのDirectX版のスマートポインタのようなもの
#include <wrl/client.h>

//DirectXAPI関係のリンク
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

//DirectXMathがDirectXのネームスペースにある
using namespace DirectX;

//ComPtr(DirectX版のスマートポインタ)
//ComPtrを付けると参照がなくった時点で解放されるようになる
using Microsoft::WRL::ComPtr;


//バッファー
//typedef ComPtr<ID3D11Buffer> ConstantBuffer, VertexBuffer, IndexBuffer, StructuredBuffer;
////typedef ComPtr<ID3D11InputLayout> InputLayout;
////typedef ComPtr<ID3D11VertexShader> VertexShader;
//typedef ComPtr<ID3D11GeometryShader> GeometryShader;
////typedef ComPtr<ID3D11PixelShader> PixelShader;
//typedef ComPtr<ID3D11ComputeShader> ComputeShader;
////typedef ComPtr<ID3D11Texture2D> Texture2D;
//typedef ComPtr<ID3D11ShaderResourceView> ShaderTexture;
//typedef ComPtr<ID3D11UnorderedAccessView> ComputeOutputView;
////typedef ComPtr<ID3D11Device>            m_pDevice;
//template<class x>

//管理クラス
class DirectX11Manager
{

private:

	//コンストラクタ
	DirectX11Manager();

	IDXGIFactory* factory;
	//GPUアダプタ
	IDXGIAdapter* adapter;
	//GPUアダプタ出力
	IDXGIOutput* adapterOutput;


	//DX11のデバイス
	ID3D11Device * m_pDevice;

	//DX11の描画命令等を送るためのもの
	ID3D11DeviceContext * m_pImContext = nullptr;
	//ハードウェアの情報が詰まっているもの
	IDXGISwapChain * m_pSwapChain = nullptr;
	//ディスプレイのバッグバッファのテクスチャ
	//Texture2D                       m_pRTTex = nullptr;
	ID3D11Texture2D* m_pDepthStencilTexture = nullptr;
	ID3D11DepthStencilView* m_pDepthStencilView = nullptr;
	//ディスプレイのバッグバッファのテクスチャを描画先として指定できるようにしたもの
	//ComPtr<ID3D11RenderTargetView>  m_pRTView = nullptr;
	ID3D11RenderTargetView * m_pRTView = nullptr;
	//ウィンドウのサイズの指定
	D3D11_VIEWPORT                  m_Viewport = { 0,0,0,0,0,0 };

	//ID3D11VertexShader * VertexShader = nullptr;
	


public:


	//デストラクタ
	~DirectX11Manager();
	//ハードウェアチェック
	HRESULT HardwareCheck();
	//デバイスとスワップチェイン作成
	HRESULT CreateDeviceAndSwapChain(HWND hWnd);

	//初期化
	HRESULT Init(HWND hWnd);
	//開放処理
	void AllRelease();

	//シングルトンインスタンスの取得
	static DirectX11Manager* GetInstance();
	//デバイスの取得
	ID3D11Device * GetDevice();
	//コンテキストの取得
	ID3D11DeviceContext * GetContext();

	//ビューポートの取得
	D3D11_VIEWPORT GetViewport();

	//頂点バッファ作成
	ID3D11Buffer* CreateVertexBuffer(int size, void* pBuffer)
	{
		//頂点バッファ作成
		D3D11_BUFFER_DESC hBufferDesc;
		hBufferDesc.ByteWidth = size;
		hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		hBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		hBufferDesc.CPUAccessFlags = 0;
		hBufferDesc.MiscFlags = 0;
		hBufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA hSubResourceData;
		hSubResourceData.pSysMem = pBuffer;
		hSubResourceData.SysMemSlicePitch = size;
		hSubResourceData.SysMemPitch = size;

		ID3D11Buffer* hpBuffer;
		if (FAILED(m_pDevice->CreateBuffer(&hBufferDesc, &hSubResourceData, &hpBuffer))) {
			return nullptr;
		}
		return hpBuffer;
	}
	
	//インデックスバッファ作成
	ID3D11Buffer* CreateIndexBuffer(UINT* Index, UINT IndexNum);

	//立方体用インデックスバッファ作成
	ID3D11Buffer* CreateCubeIndexBuffer(WORD* Index);

	//頂点バッファのセット
	void SetVertexBuffer(ID3D11Buffer* VertexBuffer, UINT VertexSize);
	//インデックスバッファのセット
	void SetIndexBuffer(ID3D11Buffer* IndexBuffer);

	//2Dテクスチャのセット
	void SetTexture2D(UINT RegisterNo, ID3D11ShaderResourceView* Texture);

	//サンプラー作成(テクスチャ描画に作成)
	ID3D11SamplerState* CreateSampler();
	//テクスチャ読み込み
	ID3D11ShaderResourceView* CreateTextureFromFile(const char * filename);
	//描画開始
	void DrawBegin();
	//描画終了
	void DrawEnd();
	//インデックス付きのプリミティブを描画
	void DrawIndexed(UINT VertexNum);
};


