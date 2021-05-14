/**
 * @file WindowManager.h
 * @brief �E�B���h�E�̊Ǘ��N���X(�V���O���g��)
 * @author �r�m�J �D��
 * @date 2020/02/05
 */

#pragma once

#include<Windows.h>

//==========================================================================
//�萔�錾
//==========================================================================
//�N���X��
#define CLASS_NAME "DirectX11 Template"
#define WINDOW_NAME "DeferredRenderer"//�E�B���h�E��
//�X�N���[���̏c����
//#define SCREEN_WIDTH	(1280)
//#define SCREEN_HEIGHT	(720)

#define SCREEN_WIDTH	(1920)
#define SCREEN_HEIGHT	(1080)


/**
* @brief �E�B���h�E�̊Ǘ��N���X
* @details ���̂Ƃ���1�������݂��Ȃ����̂Ȃ̂ŃV���O���g��
*/
class WindowManager

{
private:
	//�E�B���h�E�n���h��
	HWND hWnd;
	//���b�Z�[�W
	MSG msg;

	//�f�X�N�g�b�v�̃N���C�A���g�̈�̃T�C�Y��ۑ�����\���̕ϐ��B
	RECT DrawRectBaseCalcPos;


public:
	//�f�X�g���N�^
	~WindowManager();

	//�V���O���g���C���X�^���X�̎擾
	static WindowManager* GetInstance();


	//���b�Z�[�W�v���V�[�W����static
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//�E�B���h�E�N���X�̐ݒ�
	void RegisterWindowClass(HINSTANCE hInstance);

	//�E�B���h�E����
	bool InitializeWindow(HINSTANCE hInstance);

	//�E�B���h�E�\��
	void Show();

	//���b�Z�[�W���[�v
	bool MessageHandling(HINSTANCE hInstance);

	RECT GetRC()
	{
		return DrawRectBaseCalcPos;
	}


};
