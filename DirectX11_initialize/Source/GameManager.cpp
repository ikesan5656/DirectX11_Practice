#include "GameManager.h"
#include"DirectX11Manager.h"
#include"PolygonDraw.h"
#include"Texture2D_Draw.h"
#include "Camera.h"
#include "Polygon3D.h"

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
	//m_PolygonDraw = new PolygonDraw();
	//m_PolygonDraw->Init();
	Camera::GetInstance()->Init();
	m_Polygon3D = new Polygon3D();
	m_Polygon3D->Init();

	//m_Texture2D_Draw = new Texture2D_Draw();
	//m_Texture2D_Draw->Init();


}

void GameManager::Uninit()
{
	//m_PolygonDraw->Uninit();
	//delete m_PolygonDraw;
	m_Polygon3D->Uninit();
	delete m_Polygon3D;
	//m_Texture2D_Draw->Uninit();
	//delete m_Texture2D_Draw;

	Camera::GetInstance()->Uninit();
}

void GameManager::Update()
{
	Camera::GetInstance()->Update();
	m_Polygon3D->Update();
}

void GameManager::Draw()
{
	//���݃o�O
	Camera::GetInstance()->Draw();

	m_Polygon3D->Draw();
	//�`��J�n
	//DirectX11Manager::GetInstance()->DrawBegin();
	//m_PolygonDraw->Draw();
	//m_Texture2D_Draw->Draw();
	////�`��I��
	//DirectX11Manager::GetInstance()->DrawEnd();
}
