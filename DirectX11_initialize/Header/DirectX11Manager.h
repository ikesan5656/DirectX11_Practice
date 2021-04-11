#pragma once
/*DirectX11�̃��C�u�������Ǘ�����N���X
�V���O���g���N���X�Ƃ��ė��p
*/

//WindowsApplication���g�p����̂ŕK�{
//#include <windows.h>
//DirectX11��API
#include <d3d11.h>
////�V�F�[�_�[�̃R���p�C��
//#include <d3dcompiler.h>
//�x�N�g����FLOAT3�ȂǕ֗��ȎZ�p���C�u����(�K�{�ł͂Ȃ�)
#include <DirectXMath.h>
//�f�o�C�X�̊Ǘ������₷�����邽�߂�DirectX�ł̃X�}�[�g�|�C���^�̂悤�Ȃ���
#include <wrl/client.h>

//DirectXAPI�֌W�̃����N
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

//DirectXMath��DirectX�̃l�[���X�y�[�X�ɂ���
using namespace DirectX;

//ComPtr(DirectX�ł̃X�}�[�g�|�C���^)
//ComPtr��t����ƎQ�Ƃ��Ȃ��������_�ŉ�������悤�ɂȂ�
using Microsoft::WRL::ComPtr;


//�o�b�t�@�[
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

//�Ǘ��N���X
class DirectX11Manager
{

private:

	//�R���X�g���N�^
	DirectX11Manager();

	IDXGIFactory* factory;
	//GPU�A�_�v�^
	IDXGIAdapter* adapter;
	//GPU�A�_�v�^�o��
	IDXGIOutput* adapterOutput;


	//DX11�̃f�o�C�X
	ID3D11Device * m_pDevice;

	//DX11�̕`�施�ߓ��𑗂邽�߂̂���
	ID3D11DeviceContext * m_pImContext = nullptr;
	//�n�[�h�E�F�A�̏�񂪋l�܂��Ă������
	IDXGISwapChain * m_pSwapChain = nullptr;
	//�f�B�X�v���C�̃o�b�O�o�b�t�@�̃e�N�X�`��
	//Texture2D                       m_pRTTex = nullptr;
	ID3D11Texture2D* m_pDepthStencilTexture = nullptr;
	ID3D11DepthStencilView* m_pDepthStencilView = nullptr;
	//�f�B�X�v���C�̃o�b�O�o�b�t�@�̃e�N�X�`����`���Ƃ��Ďw��ł���悤�ɂ�������
	//ComPtr<ID3D11RenderTargetView>  m_pRTView = nullptr;
	ID3D11RenderTargetView * m_pRTView = nullptr;
	//�E�B���h�E�̃T�C�Y�̎w��
	D3D11_VIEWPORT                  m_Viewport = { 0,0,0,0,0,0 };

	//ID3D11VertexShader * VertexShader = nullptr;
	


public:


	//�f�X�g���N�^
	~DirectX11Manager();
	//�n�[�h�E�F�A�`�F�b�N
	HRESULT HardwareCheck();
	//�f�o�C�X�ƃX���b�v�`�F�C���쐬
	HRESULT CreateDeviceAndSwapChain(HWND hWnd);

	//������
	HRESULT Init(HWND hWnd);
	//�J������
	void AllRelease();

	//�V���O���g���C���X�^���X�̎擾
	static DirectX11Manager* GetInstance();
	//�f�o�C�X�̎擾
	ID3D11Device * GetDevice();
	//�R���e�L�X�g�̎擾
	ID3D11DeviceContext * GetContext();

	//�r���[�|�[�g�̎擾
	D3D11_VIEWPORT GetViewport();

	//���_�o�b�t�@�쐬
	ID3D11Buffer* CreateVertexBuffer(int size, void* pBuffer)
	{
		//���_�o�b�t�@�쐬
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
	
	//�C���f�b�N�X�o�b�t�@�쐬
	ID3D11Buffer* CreateIndexBuffer(UINT* Index, UINT IndexNum);

	//�����̗p�C���f�b�N�X�o�b�t�@�쐬
	ID3D11Buffer* CreateCubeIndexBuffer(WORD* Index);

	//���_�o�b�t�@�̃Z�b�g
	void SetVertexBuffer(ID3D11Buffer* VertexBuffer, UINT VertexSize);
	//�C���f�b�N�X�o�b�t�@�̃Z�b�g
	void SetIndexBuffer(ID3D11Buffer* IndexBuffer);

	//2D�e�N�X�`���̃Z�b�g
	void SetTexture2D(UINT RegisterNo, ID3D11ShaderResourceView* Texture);

	//�T���v���[�쐬(�e�N�X�`���`��ɍ쐬)
	ID3D11SamplerState* CreateSampler();
	//�e�N�X�`���ǂݍ���
	ID3D11ShaderResourceView* CreateTextureFromFile(const char * filename);
	//�`��J�n
	void DrawBegin();
	//�`��I��
	void DrawEnd();
	//�C���f�b�N�X�t���̃v���~�e�B�u��`��
	void DrawIndexed(UINT VertexNum);
};


