#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;
/**
* @brief テクスチャ付き3Dポリゴンクラス
* @details 3D空間上に描画するクラス
* @details 3D空間上に描画するクラス
*/

class Textured_3DPolygon
{

private:
	//バッファ
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11Buffer* m_IndexBuffer = nullptr;
	ID3D11Buffer* m_ConstantBuffer = nullptr;

	ID3D11InputLayout* m_InputLayout = nullptr;
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;

	//世界の行列
	XMMATRIX m_WorldMatrix = XMMatrixIdentity();

	float m_RotateY = 0.0f;

	//テクスチャ
	ID3D11ShaderResourceView* m_pTexture = nullptr;
	//テクスチャーのサンプラー
	ID3D11SamplerState* m_pSampler = nullptr;


public:
	Textured_3DPolygon();
	~Textured_3DPolygon();
	void Init();
	void Uninit();
	void Update();
	void Draw();
};