#include "Textured_3D_Polygon.h"
#include"DirectX11Manager.h"
#include "DX11ShaderManager.h"
#include "Camera.h"
#include "DirectInputManager.h"
#include "XInputManager.h"

//�\����
struct Textured_Vertex {
    //���[�J�����W
    float pos[3];
    //�F
    float col[4];
    //�@��
    float nor[3];
    //UV
    float uv[2];
};

Textured_Vertex g_textured_vertex_list[]{
    //��
    { { -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  0.0f,  0.0f, -1.0f }, {0.0f, 0.0f} },
    { {  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  0.0f,  0.0f, -1.0f }, {1.0f, 0.0f} },
    { { -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  0.0f,  0.0f, -1.0f }, {0.0f, 1.0f} },
    { {  0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  0.0f,  0.0f, -1.0f }, {1.0f, 1.0f} },
    //��
    { { -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f }, {  0.0f,  0.0f, 1.0f }, {0.0f, 0.0f} },
    { { -0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f }, {  0.0f,  0.0f, 1.0f }, {0.0f, 0.0f} },
    { {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f }, {  0.0f,  0.0f, 1.0f }, {0.0f, 0.0f} },
    { {  0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f }, {  0.0f,  0.0f, 1.0f }, {0.0f, 0.0f} },

    { { -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f }, { -1.0f,  0.0f,  0.0f }, {0.0f, 0.0f} },
    { { -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f }, { -1.0f,  0.0f,  0.0f }, {0.0f, 0.0f} },
    { { -0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f }, { -1.0f,  0.0f,  0.0f }, {0.0f, 0.0f} },
    { { -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f }, { -1.0f,  0.0f,  0.0f }, {0.0f, 0.0f} },

    { {  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f,  0.0f,  0.0f }, {0.0f, 0.0f} },
    { {  0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f,  0.0f,  0.0f }, {0.0f, 0.0f} },
    { {  0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f,  0.0f,  0.0f }, {0.0f, 0.0f} },
    { {  0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f,  0.0f,  0.0f }, {0.0f, 0.0f} },

    { { -0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f }, { 0.0f,  1.0f,  0.0f }, {0.0f, 0.0f} },
    { {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f }, { 0.0f,  1.0f,  0.0f }, {0.0f, 0.0f} },
    { { -0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f }, { 0.0f,  1.0f,  0.0f }, {0.0f, 0.0f} },
    { {  0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f }, { 0.0f,  1.0f,  0.0f }, {0.0f, 0.0f} },

    { { -0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f,  -1.0f,  0.0f }, {0.0f, 0.0f} },
    { { -0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f,  -1.0f,  0.0f }, {0.0f, 0.0f} },
    { {  0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f,  -1.0f,  0.0f }, {0.0f, 0.0f} },
    { {  0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f,  -1.0f,  0.0f }, {0.0f, 0.0f} },
};

WORD g_textured_index_list[]{
     0,  1,  2,     3,  2,  1,
     4,  5,  6,     7,  6,  5,
     8,  9, 10,    11, 10,  9,
    12, 13, 14,    15, 14, 13,
    16, 17, 18,    19, 18, 17,
    20, 21, 22,    23, 22, 21,
};

D3D11_INPUT_ELEMENT_DESC g_textured_vertex_desc[]{
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//�萔�o�b�t�@�\����
struct TecturedConstantBuffer {
    XMFLOAT4X4 world;
    XMFLOAT4X4 view;
    XMFLOAT4X4 projection;
    XMFLOAT4 light;
};

Textured_3DPolygon::Textured_3DPolygon()
{
}

Textured_3DPolygon::~Textured_3DPolygon()
{
}

void Textured_3DPolygon::Init()
{
    //���_�o�b�t�@�쐬
    m_VertexBuffer = DirectX11Manager::GetInstance()->CreateVertexBuffer(sizeof(g_textured_vertex_list), g_textured_vertex_list);
    //�C���f�b�N�X�o�b�t�@�쐬
    m_IndexBuffer = DirectX11Manager::GetInstance()->CreateCubeIndexBuffer(g_textured_index_list);

    //�萔�o�b�t�@�쐬(��Ɋ֐���)
    D3D11_BUFFER_DESC cbDesc;
    cbDesc.ByteWidth = sizeof(TecturedConstantBuffer);
    cbDesc.Usage = D3D11_USAGE_DEFAULT;
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbDesc.CPUAccessFlags = 0;
    cbDesc.MiscFlags = 0;
    cbDesc.StructureByteStride = 0;
    DirectX11Manager::GetInstance()->GetDevice()->CreateBuffer(&cbDesc, NULL, &m_ConstantBuffer);

    //���_���C�A�E�g�쐬
    m_InputLayout = DX11ShaderManager::GetInstance()->CreateInputLayout(g_textured_vertex_desc, 4, "Assets/Shaders/texture_3D.hlsl", "vs_main");

    //���_�V�F�[�_�쐬
    m_VertexShader = DX11ShaderManager::GetInstance()->CreateVertexShader("Assets/Shaders/texture_3D.hlsl", "vs_main");

    //�s�N�Z���V�F�[�_�쐬
    m_PixelShader = DX11ShaderManager::GetInstance()->CreatePixelShader("Assets/Shaders/texture_3D.hlsl", "ps_main");

    //�T���v���[�쐬
    m_pSampler = DirectX11Manager::GetInstance()->CreateSampler();

    //�e�N�X�`���ǂݍ���
    m_pTexture = DirectX11Manager::GetInstance()->CreateTextureFromFile("Assets/Textures/WoodenBox_simple.jpg");

}

void Textured_3DPolygon::Uninit()
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

    if (m_pSampler) {
        m_pSampler->Release();
        m_pSampler = nullptr;
    }

    if (m_pTexture) {
        m_pTexture->Release();
        m_pTexture = nullptr;
    }
}

void Textured_3DPolygon::Update()
{
    XinputManager::GetInstance()->Update();

    //�X�P�[��
    XMMATRIX scaling;
    scaling = XMMatrixScaling(1.0f, 1.0f, 1.0f);
    //��]
    XMMATRIX hRotate;
    hRotate = XMMatrixRotationY(XMConvertToRadians(m_RotateY));
    //�I�t�Z�b�g(�ړ�)
    XMMATRIX trans;
    trans = XMMatrixTranslation(0.0f, 1.0f, 0.0f);

    //�s��̏�Z
    m_WorldMatrix = scaling * hRotate * trans;

    //m_RotateY += 0.5f;

    //if (XinputManager::GetInstance()->GetKeyA()) {
    if (DirectInputManager::GetInstance()->GetKeyboardPress(DIK_LEFT)) {
        m_RotateY += 0.5f;
    }
    if (DirectInputManager::GetInstance()->GetKeyboardPress(DIK_RIGHT)) {
        m_RotateY -= 0.5f;
    }

    if (XinputManager::GetInstance()->GetPadA()) {
        m_RotateY += 0.5f;
    }
}

void Textured_3DPolygon::Draw()
{
    //m_WorldMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

//�萔�o�b�t�@�X�V
    TecturedConstantBuffer cb;
    XMStoreFloat4x4(&cb.world, XMMatrixTranspose(m_WorldMatrix));

    XMMATRIX ViewMatrix = Camera::GetInstance()->GetViewMatrix();
    XMStoreFloat4x4(&cb.view, XMMatrixTranspose(ViewMatrix));

    XMMATRIX ProjMatrix = Camera::GetInstance()->GetProjMatrix();
    XMStoreFloat4x4(&cb.projection, XMMatrixTranspose(ProjMatrix));
    // ���C�g
    //XMVECTOR light = XMVector3Normalize(XMVectorSet(0.0f, 0.5f, -1.0f, 0.0f));
    XMVECTOR light = XMVector3Normalize(XMVectorSet(-3.0f, 0.0f, 0.0f, 0.0f));
    XMStoreFloat4(&cb.light, light);

    DirectX11Manager::GetInstance()->GetContext()->UpdateSubresource(
        m_ConstantBuffer, 0, NULL, &cb, 0, 0);

    //�C���v�b�g���C�A�E�g�̃Z�b�g
    DirectX11Manager::GetInstance()->GetContext()->IASetInputLayout(m_InputLayout);
    //���_�o�b�t�@�̃Z�b�g(�����̏ꍇ)
    UINT strides = sizeof(Textured_Vertex);
    UINT offsets = 0;
    DirectX11Manager::GetInstance()->GetContext()->IASetVertexBuffers(
        0, 1, &m_VertexBuffer, &strides, &offsets);
    //�C���f�b�N�X�o�b�t�@�̃Z�b�g
    DirectX11Manager::GetInstance()->GetContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    //�v���~�e�B�u�^�C�v�̎w��
    DirectX11Manager::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    //�萔�o�b�t�@�̃Z�b�g
    DirectX11Manager::GetInstance()->GetContext()->VSSetConstantBuffers(0, 1, &m_ConstantBuffer);
    //���_�V�F�[�_�̃Z�b�g
    DirectX11Manager::GetInstance()->GetContext()->VSSetShader(m_VertexShader, NULL, 0);
    //�s�N�Z���V�F�[�_�̃Z�b�g
    DirectX11Manager::GetInstance()->GetContext()->PSSetShader(m_PixelShader, NULL, 0);

    //�e�N�X�`�����V�F�[�_�ɓn��
    DirectX11Manager::GetInstance()->GetContext()->PSSetShaderResources(0, 1, &m_pTexture);
    DirectX11Manager::GetInstance()->GetContext()->PSSetSamplers(0, 1, &m_pSampler);

    //�f�v�X�ƃX�e���V���r���[�̃N���A

    //�`�施��
    DirectX11Manager::GetInstance()->GetContext()->DrawIndexed(36, 0, 0);
}
