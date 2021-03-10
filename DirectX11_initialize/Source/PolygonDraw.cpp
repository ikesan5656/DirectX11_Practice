#include "PolygonDraw.h"

#include"DX11ShaderManager.h"


//���_���\����
struct Vertex
{
	XMFLOAT3 pos;
	XMFLOAT4 col;
};

PolygonDraw::PolygonDraw()
{

}

PolygonDraw::~PolygonDraw()
{
	//vs->Release();
}

void PolygonDraw::Init()
{
	//Shader���쐬


	//���_�V�F�[�_�쐬
	/*vs.Attach(DX11ShaderManager::GetInstance()->CreateVertexShader("Assets/Shaders/2DPipeLine.hlsl", "vsMain"));*/
	//�쐬�����o�[�e�b�N�X�V�F�[�_���擾
	VertexShader = DX11ShaderManager::GetInstance()->CreateVertexShader("Assets/Shaders/2DPipeLine.hlsl", "vsMain");
	//�쐬�����s�N�Z���V�F�[�_���擾
	PixelShader = DX11ShaderManager::GetInstance()->CreatePixelShader("Assets/Shaders/2DPipeLine.hlsl", "psMain");

	//InputLayout�̍쐬
	D3D11_INPUT_ELEMENT_DESC elem[] = {
		{ "POSITION",   0,  DXGI_FORMAT_R32G32B32_FLOAT,    0,  0,  D3D11_INPUT_PER_VERTEX_DATA,    0},
		{ "TEXCOORD",   0,  DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  12, D3D11_INPUT_PER_VERTEX_DATA,    0}
	};
	InputLayout = DX11ShaderManager::GetInstance()->CreateInputLayout(elem, 2, "Assets/Shaders/2DPipeLine.hlsl", "vsMain");

	vector<Vertex> vertexs =
	{
		{ XMFLOAT3(-0.5f,-0.5f,0), XMFLOAT4(1,0,0,1)},
		{ XMFLOAT3(0.5f,-0.5f,0), XMFLOAT4(0,1,0,1)},
		{ XMFLOAT3(0.5f, 0.5f,0), XMFLOAT4(0,0,1,1)},
		{ XMFLOAT3(-0.5f, 0.5f,0), XMFLOAT4(0,0,0,1)}
	};

	
	VertexBuffer = DirectX11Manager::GetInstance()->CreateVertexBuffer(vertexs.data(), static_cast<UINT>(vertexs.size()));

	//�C���f�b�N�X���̐ݒ�
	idxs = { 0,1,2,0,2,3 };
	
	IndexBuffer = DirectX11Manager::GetInstance()->CreateIndexBuffer(idxs.data(), static_cast<UINT>(idxs.size()));


}

void PolygonDraw::Uninit()
{
	//create�֐��Ŏg�p�����R�s�[����com�I�u�W�F�N�g�������ŉ�������
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

	if (VertexBuffer) {
		VertexBuffer->Release();
		VertexBuffer = nullptr;
	}

	if (IndexBuffer) {
		IndexBuffer->Release();
		IndexBuffer = nullptr;
	}

}

void PolygonDraw::Update()
{
}

void PolygonDraw::Draw()
{
	DX11ShaderManager::GetInstance()->SetVertexShader(VertexShader);
	DX11ShaderManager::GetInstance()->SetPixelShader(PixelShader);
	DX11ShaderManager::GetInstance()->SetInputLayout(InputLayout);
	DirectX11Manager::GetInstance()->SetVertexBuffer(VertexBuffer, sizeof(Vertex));
	DirectX11Manager::GetInstance()->SetIndexBuffer(IndexBuffer);

	DirectX11Manager::GetInstance()->DrawIndexed(static_cast<UINT>(idxs.size()));
}
