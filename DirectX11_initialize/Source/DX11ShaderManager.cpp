//#define _CRT_SECURE_NO_WARNINGS
#include "DX11ShaderManager.h"
//�V�F�[�_�R���p�C���֘A
#include <d3dcompiler.h>
#include <locale.h>
//�V�F�[�_�t�@�C�����i�[�z��
static const char *ShaderName[] = //[�e�N�X�`���t�@�C���ԍ�][�ő啶����]
{
	"Assets/Shaders/2DPipeLine.hlsl",
};


//�R���X�g���N�^
DX11ShaderManager::DX11ShaderManager()
{
}

//�f�X�g���N�^
DX11ShaderManager::~DX11ShaderManager()
{
}


ID3D11VertexShader * DX11ShaderManager::CreateVertexShader(const string & filename, const string & entrypath, bool erorr)
{
	ID3D11VertexShader* Shader;

	#if defined(_DEBUG)
		// �O���t�B�b�N�f�o�b�O�c�[���ɂ��V�F�[�_�[�̃f�o�b�O��L���ɂ���
		UINT    compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	#else
		UINT    compileFlags = 0;
	#endif

		//ComPtr<ID3DBlob> blob;
		ID3DBlob * blob = nullptr;
		size_t wLen = 0;
		wchar_t ws[512];

		setlocale(LC_CTYPE, "jpn");

		//string �������}���`�o�C�g�����̃V�[�P���X�̒����𔻕ʂ��܂��B
		//ws�ɃV�F�[�_�t�@�C���̕����񂪊i�[
		/*mbstowcs(ws, filename.c_str(), 512);*/
		mbstowcs_s(&wLen,ws, filename.c_str(), 512);
		//ComPtr<ID3DBlob> pErrorBlob = NULL;
		ID3DBlob * pErrorBlob = nullptr;

		HRESULT hr = D3DCompileFromFile(
			ws,									//�R���p�C������HLSL���L�q�����t�@�C���ւ̃p�X���w�肵�܂��B
			nullptr,							//HLSL��Ŏ��O�ɒ�`����define���w��ł��܂��B
			D3D_COMPILE_STANDARD_FILE_INCLUDE,	//�C���N���[�h�t�@�C������舵�����߂�ID3DInclude���w��ł��܂��B
			entrypath.c_str(),					//�G���g���[�|�C���g�ƂȂ�֐������w�肵�܂��B
			"vs_5_0",							//�R���p�C�����̃^�[�Q�b�g�ƂȂ�V�F�[�_���f�����w�肵�܂��B
			compileFlags,						//�R���p�C���I�v�V�������w��ł��܂��B
			0,									//�V�F�[�_���R���p�C������ꍇ�� 0 ���w�肵�܂��B
			&blob,								//�R���p�C�����ʂ̃o�C�i���R�[�h���i�[����܂��B
			&pErrorBlob							//�R���p�C���G���[���ɃG���[���e���i�[����܂��B
		);

		// �G���[�`�F�b�N.
		if (FAILED(hr))
		{
			if (erorr)
			{
				// �G���[���b�Z�[�W���o��.
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
		// �O���t�B�b�N�f�o�b�O�c�[���ɂ��V�F�[�_�[�̃f�o�b�O��L���ɂ���
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

	// �G���[�`�F�b�N.
	if (FAILED(hr))
	{
		if (erorr) {
			// �G���[���b�Z�[�W���o��.
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
		// �O���t�B�b�N�f�o�b�O�c�[���ɂ��V�F�[�_�[�̃f�o�b�O��L���ɂ���
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

	// �G���[�`�F�b�N.
	if (FAILED(hr))
	{
		// �G���[���b�Z�[�W���o��.
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

//�V���O���g���C���X�^���X�̎擾
DX11ShaderManager * DX11ShaderManager::GetInstance()
{
	static DX11ShaderManager self;

	//���g��Ԃ�
	return &self;	
}
