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
	//���g��Ԃ�
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
	////�`��J�n
	//DirectX11Manager::GetInstance()->DrawBegin();
	m_PolygonDraw->Draw();
	////�`��I��
	//DirectX11Manager::GetInstance()->DrawEnd();
}
