#include "Camera.h"
#include "DirectX11Manager.h"
#include <math.h>//���W�A���ϊ�
#include <DirectXMath.h>
#include "MathOriginal.h"

Camera* Camera::GetInstance()
{
	static Camera self;
	//���g��Ԃ�
	return &self;
}

void Camera::Init()
{
	
	m_eye = XMVectorSet(2.0f, 2.0f, -2.0f, 0.0f);
	m_focus = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	m_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	
	float m_fov = ConvertToRadians(45.0f);
	D3D11_VIEWPORT Viewport = DirectX11Manager::GetInstance()->GetViewport();
	float m_aspect = Viewport.Width / Viewport.Height;
	float m_nearZ = 0.1f;
	float m_farZ = 100.0f;
}

void Camera::Uninit()
{
}

void Camera::Update()
{
}

void Camera::Draw()
{
	//���[���h�}�g���N�X�쐬
	m_worldMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	//�r���[ �}�g���b�N�X���쐬
	m_viewMatrix = XMMatrixLookAtLH(m_eye, m_focus, m_up);
	//�v���W�F�N�V�����}�g���N�X���쐬
	m_projMatrix = XMMatrixPerspectiveFovLH(m_fov, m_aspect, m_nearZ, m_farZ);

	
}

XMMATRIX Camera::GetWorldMatrix()
{
	return m_worldMatrix;
}

XMMATRIX Camera::GetViewMatrix()
{
	return m_viewMatrix;
}

XMMATRIX Camera::GetProjMatrix()
{
	return m_projMatrix;
}
