#include "Camera.h"
#include "DirectX11Manager.h"
#include <math.h>//ラジアン変換

#include "MathOriginal.h"

Camera* Camera::GetInstance()
{
	static Camera self;
	//自身を返す
	return &self;
}

void Camera::Init()
{
	


}

void Camera::Uninit()
{

}

void Camera::Update()
{

}

void Camera::Draw()
{

	m_eye = XMVectorSet(0.0f, 2.0f, -2.0f, 0.0f);
	m_focus = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	m_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//float m_fov = ConvertToRadians(45.0f);
	float m_fov = XM_PIDIV2;
	//D3D11_VIEWPORT Viewport = DirectX11Manager::GetInstance()->GetViewport();
	float m_aspect = (float)1920 / (float)1080;
	//float m_aspect = DirectX11Manager::GetInstance()->GetViewport().Width / DirectX11Manager::GetInstance()->GetViewport().Height;
	float m_nearZ = 1.0f;
	float m_farZ = 10.0f;

	//ビュー マトリックスを作成
	m_ViewMatrix = XMMatrixLookAtLH(m_eye, m_focus, m_up);
	//プロジェクションマトリクスを作成
	m_ProjMatrix = XMMatrixPerspectiveFovLH(m_fov, m_aspect, m_nearZ, m_farZ);
	//
	
}

/*XMMATRIX Camera::GetWorldMatrix()
{
	return m_worldMatrix;
}*/

XMMATRIX Camera::GetViewMatrix()
{
	return m_ViewMatrix;
}

XMMATRIX Camera::GetProjMatrix()
{
	return m_ProjMatrix;
}
