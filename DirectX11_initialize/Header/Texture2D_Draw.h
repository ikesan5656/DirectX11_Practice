#pragma once

/**
 * @file Texture2D_Draw.h
 * @brief テクスチャー付き2Dポリゴン描画
 * @author 池ノ谷 優太
 * @date 2021/03/09
 */
#include"DirectX11Manager.h"
 //vector型を使用するため
#include <vector>
using std::vector;

/**
* @brief テクスチャ付き2Dポリゴン描画クラス
* @details 
*/

class Texture2D_Draw
{
private:
	//ウィンドウのサイズの指定
	//D3D11_VIEWPORT                  m_Viewport = { 0,0,0,0,0,0 };
	ID3D11VertexShader * VertexShader = nullptr;
	ID3D11PixelShader * PixelShader = nullptr;
	ID3D11InputLayout * InputLayout = nullptr;
	ID3D11Buffer * VertexBuffer = nullptr;
	ID3D11Buffer * IndexBuffer = nullptr;
	//テクスチャ
	ID3D11ShaderResourceView * m_pTexture = nullptr;

	ID3D11Buffer* m_pConstantBuffer = nullptr;
	ID3D11Buffer* m_pVertexBuffer = nullptr;

	ID3D11SamplerState* m_pSampler = nullptr;//テクスチャーのサンプラー
	vector<UINT> idxs;

public:
	Texture2D_Draw();
	~Texture2D_Draw();
	void Init();
	void Uninit();
	void Update();
	void Draw();

};