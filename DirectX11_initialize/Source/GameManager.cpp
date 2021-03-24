#include "GameManager.h"
#include"DirectX11Manager.h"
#include"PolygonDraw.h"
#include"Texture2D_Draw.h"

GameManager::~GameManager()
{
}

GameManager * GameManager::GetInstance()
{
	static GameManager self;
	//自身を返す
	return &self;
}


void GameManager::Init()
{
	//m_PolygonDraw = new PolygonDraw();
	//m_PolygonDraw->Init();

	m_Texture2D_Draw = new Texture2D_Draw();
	m_Texture2D_Draw->Init();

}

void GameManager::Uninit()
{
	//m_PolygonDraw->Uninit();
	//delete m_PolygonDraw;

	m_Texture2D_Draw->Uninit();
	delete m_Texture2D_Draw;
}

void GameManager::Update()
{
}

void GameManager::Draw()
{
	////描画開始
	//DirectX11Manager::GetInstance()->DrawBegin();
	//m_PolygonDraw->Draw();
	m_Texture2D_Draw->Draw();
	////描画終了
	//DirectX11Manager::GetInstance()->DrawEnd();
}
