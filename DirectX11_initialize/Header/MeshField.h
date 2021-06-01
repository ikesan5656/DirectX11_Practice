#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

#define MESH_DEPTH (4)	//奥行
#define MESH_WIDHT (4)	//幅
#define VERTEX_COUNT ((MESH_WIDHT + 1) * (MESH_DEPTH + 1))
//インデックスの要素数
#define INDEX_COUNT ((((MESH_DEPTH + 1) * 2)*MESH_DEPTH + (MESH_WIDHT * 2) -1))
//構造体
struct Vertex_mesh_field {
	//ローカル座標
	float pos[3];
	//色
	float col[4];
	//法線
	float nor[3];
};

/*
* メッシュフィールドクラス
*/
class MeshField {

private:
	int mesh_depth_vertex;
	int mesh_width_vertex;
	//頂点情報
	Vertex_mesh_field m_vertex_data[MESH_DEPTH + 1][MESH_WIDHT + 1];
	//頂点インデックス
	WORD m_IndexList[INDEX_COUNT];


	//バッファ
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11Buffer* m_IndexBuffer = nullptr;
	ID3D11Buffer* m_ConstantBuffer = nullptr;

	ID3D11InputLayout* m_InputLayout = nullptr;
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;

	//世界の行列
	XMMATRIX m_WorldMatrix = XMMatrixIdentity();

public:
	MeshField();
	~MeshField();
	void Init();
	void Uninit();
	void Update();
	void Draw();

};