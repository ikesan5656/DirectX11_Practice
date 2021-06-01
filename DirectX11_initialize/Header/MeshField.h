#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

#define MESH_DEPTH (4)	//���s
#define MESH_WIDHT (4)	//��
#define VERTEX_COUNT ((MESH_WIDHT + 1) * (MESH_DEPTH + 1))
//�C���f�b�N�X�̗v�f��
#define INDEX_COUNT ((((MESH_DEPTH + 1) * 2)*MESH_DEPTH + (MESH_WIDHT * 2) -1))
//�\����
struct Vertex_mesh_field {
	//���[�J�����W
	float pos[3];
	//�F
	float col[4];
	//�@��
	float nor[3];
};

/*
* ���b�V���t�B�[���h�N���X
*/
class MeshField {

private:
	int mesh_depth_vertex;
	int mesh_width_vertex;
	//���_���
	Vertex_mesh_field m_vertex_data[MESH_DEPTH + 1][MESH_WIDHT + 1];
	//���_�C���f�b�N�X
	WORD m_IndexList[INDEX_COUNT];


	//�o�b�t�@
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11Buffer* m_IndexBuffer = nullptr;
	ID3D11Buffer* m_ConstantBuffer = nullptr;

	ID3D11InputLayout* m_InputLayout = nullptr;
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;

	//���E�̍s��
	XMMATRIX m_WorldMatrix = XMMatrixIdentity();

public:
	MeshField();
	~MeshField();
	void Init();
	void Uninit();
	void Update();
	void Draw();

};