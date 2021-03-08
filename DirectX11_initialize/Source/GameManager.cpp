#include "GameManager.h"
#include"DirectX11Manager.h"
#include"PolygonDraw.h"
GameManager::GameManager()
{
}

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
	m_PolygonDraw = new PolygonDraw();
	m_PolygonDraw->Init();
}

void GameManager::Uninit()
{
	m_PolygonDraw->Uninit();
	delete m_PolygonDraw;
}

void GameManager::Update()
{
}

void GameManager::Draw()
{
	////描画開始
	//DirectX11Manager::GetInstance()->DrawBegin();
	m_PolygonDraw->Draw();
	////描画終了
	//DirectX11Manager::GetInstance()->DrawEnd();
}
