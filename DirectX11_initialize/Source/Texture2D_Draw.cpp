#include "Texture2D_Draw.h"
#include"DX11ShaderManager.h"
#include"TextureManager.h"
#include "TextureManager.h"

//���_���\����
struct Vertex
{
	XMFLOAT3 pos;
	XMFLOAT4 col;
	XMFLOAT2 uv;
};

Texture2D_Draw::Texture2D_Draw()
{
	//�쐬�����o�[�e�b�N�X�V�F�[�_���擾
	VertexShader = DX11ShaderManager::GetInstance()->CreateVertexShader("2DPipeLine.hlsl", "vsMain");
	//�쐬�����s�N�Z���V�F�[�_���擾
	PixelShader = DX11ShaderManager::GetInstance()->CreatePixelShader("2DPipeLine.hlsl", "psMain");
	//�e�N�X�`�����擾
	//texture = TextureManager::GetInstance()->CreateTextureFromFile("")
}

Texture2D_Draw::~Texture2D_Draw()
{

}

void Texture2D_Draw::Init()
{

}

void Texture2D_Draw::Uninit()
{

}

void Texture2D_Draw::Update()
{

}

void Texture2D_Draw::Draw()
{

}