#include"WindowManager.h"
#include <crtdbg.h>
//�E�B���h�E�֘A
#pragma comment(lib, "winmm.lib")
//==========================================================================
//�萔�錾
//==========================================================================


//==========================================================================
//�v���g�^�C�v�錾
//==========================================================================


//==========================================================================
//�O���[�o���ϐ�
//==========================================================================


//===========
//���C���֐�
//===========
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// �q�[�v���������m��
	/*int *pNumber = new int[3];
	pNumber[0] = 1;
	pNumber[1] = 2;
	pNumber[2] = 3;*/


	//�E�B���h�E�N���X�̐ݒ�
	WindowManager::GetInstance()->RegisterWindowClass(hInstance);

	//�E�B���h�E����
	WindowManager::GetInstance()->InitializeWindow(hInstance);

	//���b�Z�[�W���[�v
	WindowManager::GetInstance()->MessageHandling(hInstance);

	return 0;
}



