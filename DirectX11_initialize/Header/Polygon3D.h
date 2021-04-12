#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;
/**
* @brief 3D�|���S���N���X
* @details 3D��ԏ�ɕ`�悷��N���X
* @details 3D��ԏ�ɕ`�悷��N���X
*/

class Polygon3D
{

private:
	//�o�b�t�@
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11Buffer* m_IndexBuffer = nullptr;
	ID3D11Buffer* m_ConstantBuffer = nullptr;

	ID3D11InputLayout* m_InputLayout = nullptr;
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;

	//���E�̍s��
	XMMATRIX m_WorldMatrix;

public:
	Polygon3D();
	~Polygon3D();
	void Init();
	void Uninit();
	void Update();
	void Draw();
};