#include "Texture2D_Draw.h"
#include"DX11ShaderManager.h"
#include"TextureManager.h"
#include "TextureManager.h"

//頂点情報構造体
struct Vertex
{
	XMFLOAT3 pos;
	XMFLOAT4 col;
	XMFLOAT2 uv;
};

Texture2D_Draw::Texture2D_Draw()
{
	//作成したバーテックスシェーダを取得
	VertexShader = DX11ShaderManager::GetInstance()->CreateVertexShader("2DPipeLine.hlsl", "vsMain");
	//作成したピクセルシェーダを取得
	PixelShader = DX11ShaderManager::GetInstance()->CreatePixelShader("2DPipeLine.hlsl", "psMain");
	//テクスチャを取得
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