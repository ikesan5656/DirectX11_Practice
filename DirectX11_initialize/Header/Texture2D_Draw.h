#pragma once

/**
 * @file Texture2D_Draw.h
 * @brief �e�N�X�`���[�t��2D�|���S���`��
 * @author �r�m�J �D��
 * @date 2021/03/09
 */
#include"DirectX11Manager.h"
 //vector�^���g�p���邽��
#include <vector>
using std::vector;

/**
* @brief �e�N�X�`���t��2D�|���S���`��N���X
* @details 
*/

class Texture2D_Draw
{
private:
	//�E�B���h�E�̃T�C�Y�̎w��
	//D3D11_VIEWPORT                  m_Viewport = { 0,0,0,0,0,0 };
	ID3D11VertexShader * VertexShader = nullptr;
	ID3D11PixelShader * PixelShader = nullptr;
	ID3D11InputLayout * InputLayout = nullptr;
	ID3D11Buffer * VertexBuffer = nullptr;
	ID3D11Buffer * IndexBuffer = nullptr;
	//�e�N�X�`��
	ID3D11ShaderResourceView * m_pTexture = nullptr;

	ID3D11Buffer* m_pConstantBuffer = nullptr;
	ID3D11Buffer* m_pVertexBuffer = nullptr;

	ID3D11SamplerState* m_pSampler = nullptr;//�e�N�X�`���[�̃T���v���[
	vector<UINT> idxs;

public:
	Texture2D_Draw();
	~Texture2D_Draw();
	void Init();
	void Uninit();
	void Update();
	void Draw();

};