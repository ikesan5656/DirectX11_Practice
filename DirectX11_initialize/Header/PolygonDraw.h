/**
 * @file PolygonDraw.h
 * @brief ポリゴン描画
 * @author 池ノ谷 優太
 * @date 2020/02/10
 */

#pragma once
#include"DirectX11Manager.h"
 //vector型を使用するため
#include <vector>
using std::vector;

 /**
 * @brief ポリゴン描画クラス
 * @details 一番簡単なポリゴンを描画するだけのクラス
 */


class PolygonDraw
{

private:

	//VertexShader vs;
	ID3D11VertexShader * VertexShader = nullptr;
	ID3D11PixelShader * PixelShader = nullptr;
	//PixelShader ps;
	ID3D11InputLayout * InputLayout = nullptr;
	//InputLayout il;
	//VertexBuffer vb;
	ID3D11Buffer * VertexBuffer = nullptr;
	//IndexBuffer ib;
	ID3D11Buffer * IndexBuffer = nullptr;

	vector<UINT> idxs;

public:

	//コンストラクタ
	PolygonDraw();
	//デストラクタ
	~PolygonDraw();

	void Init();
	void Uninit();
	void Update();
	void Draw();


};
