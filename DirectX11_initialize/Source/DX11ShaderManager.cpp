//#define _CRT_SECURE_NO_WARNINGS
#include "DX11ShaderManager.h"
//シェーダコンパイラ関連
#include <d3dcompiler.h>
#include <locale.h>
//シェーダファイル名格納配列
static const char *ShaderName[] = //[テクスチャファイル番号][最大文字列]
{
	"Assets/Shaders/2DPipeLine.hlsl",
};


//コンストラクタ
DX11ShaderManager::DX11ShaderManager()
{
}

//デストラクタ
DX11ShaderManager::~DX11ShaderManager()
{
}


ID3D11VertexShader * DX11ShaderManager::CreateVertexShader(const string & filename, const string & entrypath, bool erorr)
{
	ID3D11VertexShader* Shader;

	#if defined(_DEBUG)
		// グラフィックデバッグツールによるシェーダーのデバッグを有効にする
		UINT    compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	#else
		UINT    compileFlags = 0;
	#endif

		//ComPtr<ID3DBlob> blob;
		ID3DBlob * blob = nullptr;
		size_t wLen = 0;
		wchar_t ws[512];

		setlocale(LC_CTYPE, "jpn");

		//string が示すマルチバイト文字のシーケンスの長さを判別します。
		//wsにシェーダファイルの文字列が格納
		/*mbstowcs(ws, filename.c_str(), 512);*/
		mbstowcs_s(&wLen,ws, filename.c_str(), 512);
		//ComPtr<ID3DBlob> pErrorBlob = NULL;
		ID3DBlob * pErrorBlob = nullptr;

		HRESULT hr = D3DCompileFromFile(
			ws,									//コンパイルするHLSLを記述したファイルへのパスを指定します。
			nullptr,							//HLSL上で事前に定義するdefineを指定できます。
			D3D_COMPILE_STANDARD_FILE_INCLUDE,	//インクルードファイルを取り扱うためのID3DIncludeを指定できます。
			entrypath.c_str(),					//エントリーポイントとなる関数名を指定します。
			"vs_5_0",							//コンパイル時のターゲットとなるシェーダモデルを指定します。
			compileFlags,						//コンパイルオプションを指定できます。
			0,									//シェーダをコンパイルする場合は 0 を指定します。
			&blob,								//コンパイル結果のバイナリコードが格納されます。
			&pErrorBlob							//コンパイルエラー時にエラー内容が格納されます。
		);

		// エラーチェック.
		if (FAILED(hr))
		{
			if (erorr)
			{
				// エラーメッセージを出力.
				if (pErrorBlob != NULL)
				{
					MessageBox(NULL, (char*)pErrorBlob->GetBufferPointer(), "", 0);
					return nullptr;
				}
			}
			else
			{
				string er = (char*)pErrorBlob->GetBufferPointer();
				if (er.find("entrypoint not found") == string::npos)
					MessageBox(NULL, (char*)pErrorBlob->GetBufferPointer(), "", 0);;
				//cout << filename << "(" << entrypath << ") is notfound" << endl;
				return nullptr;
			}
		}
		
		hr = DirectX11Manager::GetInstance()->GetDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &Shader);
		assert(SUCCEEDED(hr));

		blob->Release();
		blob = nullptr;

		if (pErrorBlob) {
			pErrorBlob->Release();
			pErrorBlob = nullptr;
		}

		return Shader;
}

ID3D11PixelShader * DX11ShaderManager::CreatePixelShader(const string & filename, const string & entrypath, bool erorr)
{
	ID3D11PixelShader* Shader;

	#if defined(_DEBUG)
		// グラフィックデバッグツールによるシェーダーのデバッグを有効にする
		UINT    compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	#else
		UINT    compileFlags = 0;
	#endif
	//ComPtr<ID3DBlob> blob;
	ID3DBlob * blob = nullptr;
	size_t wLen = 0;
	wchar_t ws[512];

	setlocale(LC_CTYPE, "jpn");
	//mbstowcs(ws, filename.c_str(), 512);
	mbstowcs_s(&wLen, ws, filename.c_str(), 512);
	//ComPtr<ID3DBlob> pErrorBlob = NULL;
	ID3DBlob * pErrorBlob = nullptr;

	HRESULT hr = D3DCompileFromFile(
		ws,
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entrypath.c_str(),
		"ps_5_0",
		compileFlags,
		0,
		&blob,
		&pErrorBlob);

	// エラーチェック.
	if (FAILED(hr))
	{
		if (erorr) {
			// エラーメッセージを出力.
			if (pErrorBlob != NULL && erorr)
			{
				MessageBox(NULL, (char*)pErrorBlob->GetBufferPointer(), "", 0);
				return nullptr;
			}
		}
		else
		{
			string er = (char*)pErrorBlob->GetBufferPointer();
			if (er.find("entrypoint not found") == string::npos)
				MessageBox(NULL, (char*)pErrorBlob->GetBufferPointer(), "", 0);;
			//cout << filename << "(" << entrypath << ") is notfound" << endl;
			return nullptr;
		}
	}

	hr = DirectX11Manager::GetInstance()->GetDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &Shader);
	assert(SUCCEEDED(hr));

	if (blob) {
		blob->Release();
		blob = nullptr;
	}

	if (pErrorBlob) {
		pErrorBlob->Release();
		pErrorBlob = nullptr;
	}
	return Shader;
	
}

ID3D11InputLayout * DX11ShaderManager::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC * layout, UINT elem_num, const string & filename, const string & entrypath)
{
	ID3D11InputLayout* pVertexLayout;

	#if defined(_DEBUG)
		// グラフィックデバッグツールによるシェーダーのデバッグを有効にする
		UINT    compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	#else
		UINT    compileFlags = 0;
	#endif
	//ComPtr<ID3DBlob> blob;
	ID3DBlob * blob = nullptr;
	size_t wLen = 0;
	wchar_t ws[512];

	setlocale(LC_CTYPE, "jpn");
	//mbstowcs(ws, filename.c_str(), 512);
	mbstowcs_s(&wLen, ws, filename.c_str(), 512);
	//ComPtr<ID3DBlob> pErrorBlob = NULL;
	ID3DBlob * pErrorBlob = nullptr;

	HRESULT hr = D3DCompileFromFile(
		ws,
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entrypath.c_str(),
		"vs_5_0",
		compileFlags,
		0,
		&blob,
		&pErrorBlob);

	// エラーチェック.
	if (FAILED(hr))
	{
		// エラーメッセージを出力.
		if (pErrorBlob != NULL)
		{
			MessageBox(NULL, (char*)pErrorBlob->GetBufferPointer(), "", 0);
		}
	}
	hr = DirectX11Manager::GetInstance()->GetDevice()->CreateInputLayout(
		layout, 
		elem_num, 
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		&pVertexLayout);
	assert(SUCCEEDED(hr));

	if (blob) {
		blob->Release();
		blob = nullptr;
	}

	if (pErrorBlob) {
		pErrorBlob->Release();
		pErrorBlob = nullptr;
	}
	return pVertexLayout;

}

void DX11ShaderManager::SetInputLayout(ID3D11InputLayout * VertexLayout)
{
	DirectX11Manager::GetInstance()->GetContext()->IASetInputLayout(VertexLayout);
}

void DX11ShaderManager::SetVertexShader(ID3D11VertexShader * vs)
{
	DirectX11Manager::GetInstance()->GetContext()->VSSetShader(vs, nullptr, 0);
}

void DX11ShaderManager::SetPixelShader(ID3D11PixelShader * ps)
{

	DirectX11Manager::GetInstance()->GetContext()->PSSetShader(ps, nullptr, 0);
}

//シングルトンインスタンスの取得
DX11ShaderManager * DX11ShaderManager::GetInstance()
{
	static DX11ShaderManager self;

	//自身を返す
	return &self;	
}
