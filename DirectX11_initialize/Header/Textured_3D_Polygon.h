#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;
/**
* @brief �e�N�X�`���t��3D�|���S���N���X
* @details 3D��ԏ�ɕ`�悷��N���X
* @details 3D��ԏ�ɕ`�悷��N���X
*/

class Textured_3DPolygon
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
	XMMATRIX m_WorldMatrix = XMMatrixIdentity();

	float m_RotateY = 0.0f;

	//�e�N�X�`��
	ID3D11ShaderResourceView* m_pTexture = nullptr;
	//�e�N�X�`���[�̃T���v���[
	ID3D11SamplerState* m_pSampler = nullptr;


public:
	Textured_3DPolygon();
	~Textured_3DPolygon();
	void Init();
	void Uninit();
	void Update();
	void Draw();
};