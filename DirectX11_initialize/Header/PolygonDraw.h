/**
 * @file PolygonDraw.h
 * @brief �|���S���`��
 * @author �r�m�J �D��
 * @date 2020/02/10
 */

#pragma once
#include"DirectX11Manager.h"
 //vector�^���g�p���邽��
#include <vector>
using std::vector;

 /**
 * @brief �|���S���`��N���X
 * @details ��ԊȒP�ȃ|���S����`�悷�邾���̃N���X
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

	//�R���X�g���N�^
	PolygonDraw();
	//�f�X�g���N�^
	~PolygonDraw();

	void Init();
	void Uninit();
	void Update();
	void Draw();


};
