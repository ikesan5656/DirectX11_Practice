#include "Polygon3D.h"
#include"DirectX11Manager.h"
#include "DX11ShaderManager.h"
//DirectXMath��DirectX�̃l�[���X�y�[�X�ɂ���
using namespace DirectX;
//�\����
struct Vertex {
    float pos[3];
    float col[4];
};

Vertex g_VertexList[]{
    { { -0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
    { {  0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
    { { -0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
    { {  0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },

    { { -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
    { { -0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
    { {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
    { {  0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },

    { { -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
    { { -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
    { { -0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
    { { -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },

    { {  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
    { {  0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
    { {  0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
    { {  0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },

    { { -0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },
    { {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },
    { { -0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },
    { {  0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },

    { { -0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
    { { -0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
    { {  0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
    { {  0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
};

WORD g_IndexList[]{
     0,  1,  2,     3,  2,  1,
     4,  5,  6,     7,  6,  5,
     8,  9, 10,    11, 10,  9,
    12, 13, 14,    15, 14, 13,
    16, 17, 18,    19, 18, 17,
    20, 21, 22,    23, 22, 21,
};

D3D11_INPUT_ELEMENT_DESC g_VertexDesc[]{
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//�萔�o�b�t�@�\����
struct ConstantBuffer {
    XMFLOAT4X4 world;
    XMFLOAT4X4 view;
    XMFLOAT4X4 projection;
};

void Polygon3D::Init()
{
    //���_�o�b�t�@�쐬
    m_VertexBuffer = DirectX11Manager::GetInstance()->CreateVertexBuffer(sizeof(g_VertexList), g_VertexList);
    //�C���f�b�N�X�o�b�t�@�쐬
    m_IndexBuffer = DirectX11Manager::GetInstance()->CreateCubeIndexBuffer(g_IndexList);

    //�萔�o�b�t�@�쐬(��Ɋ֐���)
    D3D11_BUFFER_DESC cbDesc;
    cbDesc.ByteWidth = sizeof(ConstantBuffer);
    cbDesc.Usage = D3D11_USAGE_DEFAULT;
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbDesc.CPUAccessFlags = 0;
    cbDesc.MiscFlags = 0;
    cbDesc.StructureByteStride = 0;
    DirectX11Manager::GetInstance()->GetDevice()->CreateBuffer(&cbDesc, NULL, &m_ConstantBuffer);

    //���_���C�A�E�g�쐬
    m_InputLayout = DX11ShaderManager::GetInstance()->CreateInputLayout(g_VertexDesc, 2, "Assets/Shaders/3DPipeLine.hlsl", "vs_main");

    //���_�V�F�[�_�쐬
    m_VertexShader = DX11ShaderManager::GetInstance()->CreateVertexShader("Assets/Shaders/3DPipeLine.hlsl", "vs_main");

    //�s�N�Z���V�F�[�_�쐬
    m_PixelShader = DX11ShaderManager::GetInstance()->CreatePixelShader("Assets/Shaders/3DPipeLine.hlsl", "ps_main");


}
    
void Polygon3D::Uninit()
{
    if (m_VertexBuffer) {
        m_VertexBuffer->Release();
        m_VertexBuffer = nullptr;
    }

    if (m_IndexBuffer) {
        m_IndexBuffer->Release();
        m_IndexBuffer = nullptr;
    }

    if (m_ConstantBuffer) {
        m_ConstantBuffer->Release();
        m_ConstantBuffer = nullptr;
    }

    if (m_InputLayout) {
        m_InputLayout->Release();
        m_InputLayout = nullptr;
    }

    if (m_VertexShader) {
        m_VertexShader->Release();
        m_VertexShader = nullptr;
    }

    if (m_PixelShader) {
        m_PixelShader->Release();
        m_PixelShader = nullptr;
    }
}

void Polygon3D::Update()
{

}

void Polygon3D::Draw()
{
    //���[���h�}�g���N�X�쐬
    m_worldMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
}
