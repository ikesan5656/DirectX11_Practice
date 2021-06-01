#include "MeshField.h"
#include"DirectX11Manager.h"
#include "DX11ShaderManager.h"
#include "Camera.h"


//�萔�o�b�t�@�\����
struct ConstantBuffer {
	XMFLOAT4X4 world;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
};

MeshField::MeshField()
{
	//���s�A���̒��_���̏�����
	mesh_depth_vertex = MESH_DEPTH + 1;
	mesh_width_vertex = MESH_WIDHT + 1;

	//�`��J�n�n�_���W�̎w��
	float default_x = -(float)MESH_WIDHT / 2;
	float default_z = (float)MESH_DEPTH / 2;
	float default_y = 0.0f;

	//���_���̐ݒ�
	for (int countZ = 0; countZ < mesh_depth_vertex; countZ++) {
		for (int countX = 0; countX < mesh_width_vertex; countX++) {
			m_vertex_data[countZ][countX] = { {default_x + countX, 0.0f, default_z - countZ},  {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f} };
		}
	}

	int index_num = 0;

	//�C���f�b�N�X���̐ݒ�
	for (int countZ = 0; countZ < mesh_depth_vertex; countZ++) {

		if (!countZ == 0) {
				m_IndexList[index_num] = (mesh_width_vertex) * (countZ + 1);
				index_num++;
		}

		for (int countX = 0; countX < mesh_width_vertex; countX++) {
			m_IndexList[index_num] = (mesh_width_vertex + countX) + (mesh_width_vertex * countZ);
			index_num++;
			m_IndexList[index_num] = countX + (mesh_width_vertex * countZ);
			index_num++;
		}
		m_IndexList[index_num] = MESH_WIDHT + (mesh_width_vertex * countZ);
		index_num++;
	}

	/*int index_num = 0;

	//�C���f�b�N�X���̐ݒ�
	for (int countZ = 0; countZ < MESH_DEPTH + 1; countZ++) {

		if (!countZ == 0) {
			m_IndexList[index_num] = (MESH_WIDHT + 1) * (countZ + 1);
			index_num++;
		}

		for (int countX = 0; countX < MESH_WIDHT + 1; countX++) {
			m_IndexList[index_num] = (MESH_WIDHT + 1 + countX) + ((MESH_WIDHT + 1) * countZ);
			index_num++;
			m_IndexList[index_num] = countX + ((MESH_WIDHT + 1) * countZ);
			index_num++;
		}
		m_IndexList[index_num] = MESH_WIDHT + ((MESH_WIDHT + 1) * countZ);
		index_num++;
	}*/
		

}

MeshField::~MeshField()
{
}

void MeshField::Init()
{
	//���_���C�A�E�g
	D3D11_INPUT_ELEMENT_DESC g_VertexDesc[]{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	//���_�o�b�t�@�쐬
	m_VertexBuffer = DirectX11Manager::GetInstance()->CreateVertexBuffer(sizeof(m_vertex_data), m_vertex_data);
	//�C���f�b�N�X�o�b�t�@�쐬
	m_IndexBuffer = DirectX11Manager::GetInstance()->CreateIndexBuffer(m_IndexList, INDEX_COUNT);

	//�萔�o�b�t�@�쐬
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(ConstantBuffer);
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;
	DirectX11Manager::GetInstance()->GetDevice()->CreateBuffer(&cbDesc, NULL, &m_ConstantBuffer);

	//���_���C�A�E�g�쐬
	m_InputLayout = DX11ShaderManager::GetInstance()->CreateInputLayout(g_VertexDesc, 3, "Assets/Shaders/3DPipeLine.hlsl", "vs_main");

	//���_�V�F�[�_�쐬
	 m_VertexShader = DX11ShaderManager::GetInstance()->CreateVertexShader("Assets/Shaders/3DPipeLine.hlsl", "vs_main");

	 //�s�N�Z���V�F�[�_�쐬
	 m_PixelShader = DX11ShaderManager::GetInstance()->CreatePixelShader("Assets/Shaders/3DPipeLine.hlsl", "ps_main");

}

void MeshField::Uninit()
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

void MeshField::Update()
{
	//�X�P�[��
	XMMATRIX scaling;
	scaling = XMMatrixScaling(1.0f, 1.0f, 1.0f);

	//�I�t�Z�b�g(�ړ�)
	XMMATRIX trans;
	trans = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	//�s���Z
	m_WorldMatrix = scaling * trans;
}

void MeshField::Draw()
{
	//�萔�o�b�t�@�X�V
	ConstantBuffer cb;
	XMStoreFloat4x4(&cb.world, XMMatrixTranspose(m_WorldMatrix));

	XMMATRIX ViewMatrix = Camera::GetInstance()->GetViewMatrix();
	XMStoreFloat4x4(&cb.view, XMMatrixTranspose(ViewMatrix));

	XMMATRIX ProjMatrix = Camera::GetInstance()->GetProjMatrix();
	XMStoreFloat4x4(&cb.projection, XMMatrixTranspose(ProjMatrix));

	DirectX11Manager::GetInstance()->GetContext()->UpdateSubresource(
		m_ConstantBuffer, 0, NULL, &cb, 0, 0);

	//�C���v�b�g���C�A�E�g�̃Z�b�g
	DirectX11Manager::GetInstance()->GetContext()->IASetInputLayout(m_InputLayout);
	//���_�o�b�t�@�̃Z�b�g(�����̏ꍇ)
	UINT strides = sizeof(Vertex_mesh_field);
	UINT offsets = 0;
	DirectX11Manager::GetInstance()->GetContext()->IASetVertexBuffers(
		0, 1, &m_VertexBuffer, &strides, &offsets);
	//�C���f�b�N�X�o�b�t�@�̃Z�b�g
	DirectX11Manager::GetInstance()->GetContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	//�v���~�e�B�u�^�C�v�̎w��
	DirectX11Manager::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//�萔�o�b�t�@�̃Z�b�g
	DirectX11Manager::GetInstance()->GetContext()->VSSetConstantBuffers(0, 1, &m_ConstantBuffer);
	//���_�V�F�[�_�̃Z�b�g
	DirectX11Manager::GetInstance()->GetContext()->VSSetShader(m_VertexShader, NULL, 0);
	//�s�N�Z���V�F�[�_�̃Z�b�g
	DirectX11Manager::GetInstance()->GetContext()->PSSetShader(m_PixelShader, NULL, 0);

	//�`�施��
	DirectX11Manager::GetInstance()->GetContext()->DrawIndexed(INDEX_COUNT, 0, 0);
}
