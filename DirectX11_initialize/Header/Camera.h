#pragma once
#include <DirectXMath.h>
using namespace DirectX;

/**
* @brief �J�����N���X
* @details DX11�Ŏg�p����J�������Ǘ�����N���X
*/

/*
�萔�o�b�t�@�͂��ꂼ��̃I�u�W�F�N�g�N���X�ō쐬�A�Z�b�g����
*/

class Camera 
{

	private:
		//���E�̍s��
		XMMATRIX m_worldMatrix;
		//�J�����̈ʒu
		XMVECTOR m_eye;
		//�J�����̒����_�̈ʒu
		XMVECTOR m_focus;
		//���[���h���W�̏�����̃x�N�g��
		XMVECTOR m_up;
		//�r���[�}�g���N�X
		XMMATRIX m_viewMatrix;

		float m_fov;
		float m_aspect;
		float m_nearZ;
		float m_farZ;
		//�v���W�F�N�V�����}�g���N�X
		XMMATRIX m_projMatrix;

	public:
		//�V���O���g���C���X�^���X�̎擾
		static Camera* GetInstance();
		void Init();
		void Uninit();
		void Update();
		void Draw();

		//�������牺�̓Q�b�^�[
		XMMATRIX GetWorldMatrix();
		XMMATRIX GetViewMatrix();
		XMMATRIX GetProjMatrix();


};