#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;
/**
* @brief 3Dポリゴンクラス
* @details 3D空間上に描画するクラス
* @details 3D空間上に描画するクラス
*/

class Polygon3D
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
	XMMATRIX m_WorldMatrix;

public:
	Polygon3D();
	~Polygon3D();
	void Init();
	void Uninit();
	void Update();
	void Draw();
};