/**
 * @file WindowManager.cpp
 * @brief �E�B���h�E�̊Ǘ�
 * @author �r�m�J �D��
 * @date 2020/02/05
 */
#include "WindowManager.h"
#include"DirectX11Manager.h"
#include"GameManager.h"

//�R���X�g���N�^
WindowManager::WindowManager()
{
	
}

//�f�X�g���N�^
WindowManager::~WindowManager()
{

}

//�V���O���g���C���X�^���X�̎擾
WindowManager * WindowManager::GetInstance()
{
	static WindowManager self;
	//���g��Ԃ�
	return &self;
}

LRESULT CALLBACK WindowManager::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	#ifdef _DEBUG

		//if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))//ImGui�̃v���V�[�W��
		//	return true;

	#endif

	int nID;

	switch (uMsg)
	{

	case WM_SIZE:

		#ifdef _DEBUG
				//CImGui_Manager::CreateDevice();
		#endif
				break;

	case WM_DESTROY:
		PostQuitMessage(0);//WM_QUIT���b�Z�[�W�̑��M
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{

		case VK_ESCAPE://[ESC]�L�[�������ꂽ

			#ifdef _DEBUG//�f�o�b�O�������ɃA�v�������
						PostQuitMessage(0);//WM_QUIT���b�Z�[�W�̑��M
			#endif

			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			break;
		}

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void WindowManager::RegisterWindowClass(HINSTANCE hInstance)
{
	//�E�B���h�E�N���X�̐ݒ�
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),		//�T�C�Y
		CS_CLASSDC,				//�X�^�C��
		WindowManager::WndProc,				//�v���V�[�W���֐�
		0L,						//���i�͎g��Ȃ�
		0L,						//���i�͎g��Ȃ�
		hInstance,
		NULL,
		NULL,
		NULL,
		NULL,
		CLASS_NAME,	//�E�B���h�E�N���X�l�[��
		NULL
	};

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);//�E�B���h�E�N���X�œo�^
}

bool WindowManager::InitializeWindow(HINSTANCE hInstance)
{
	//�E�B���h�E�T�C�Y�̎w��
	RECT WindowRect = { (LONG)0, (LONG)0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
	//�E�B���h�E�̃X�^�C�����w��
	AdjustWindowRect(&WindowRect, WS_OVERLAPPEDWINDOW ^WS_MAXIMIZEBOX ^WS_THICKFRAME, false);

	//�E�B���h�E�̔�N���C�A���g�̈�̕��ƍ������l�������N���C�A���g�̈�̌v�Z�B
	int WindowWidth = WindowRect.right - WindowRect.left;
	int WindowHeight = WindowRect.bottom - WindowRect.top;

	////�f�X�N�g�b�v�̃N���C�A���g�̈�̃T�C�Y��ۑ�����\���̕ϐ��B
	//RECT DrawRectBaseCalcPos;

	//�f�X�N�g�b�v�̃N���C�A���g�̈�(��ʉ𑜓x)���擾����B
	GetWindowRect(GetDesktopWindow(), &DrawRectBaseCalcPos);

	//�E�B���h�E�̒��S���W���f�X�N�g�b�v�̒��S���W�ɂȂ�悤�ɁA�f�X�N�g�b�v��ł̃E�B���h�E�̍��㐶�����W���v�Z�B
	int DrawRectPosX = ((DrawRectBaseCalcPos.right - DrawRectBaseCalcPos.left) - WindowWidth) / 2;
	int DrawRectPosY = ((DrawRectBaseCalcPos.bottom - DrawRectBaseCalcPos.top) - WindowHeight) / 2;

	
	//���C���E�B���h�E�̍쐬
	hWnd = CreateWindowEx(//�E�B���h�E�쐬
		0,//�h���b�O�A���h�h���b�v
		CLASS_NAME,//�N���X��
		WINDOW_NAME,//�E�B���h�E���i�^�C�g���j
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX /*| WS_VSCROLL*/,//�f�t�H���g�E�B���h�E�X�^�C��
																			//WS_POPUP,
		//x,//�E�B���h�E����X���W
		//y,//�E�B���h�E����Y���W
		DrawRectPosX,
		DrawRectPosY + 16,
		WindowWidth,//��
		WindowHeight,//����
		NULL,//�e�E�B���h�E�ւ̃n���h��
		NULL,//���j���[�n���h���i���e�j
		hInstance,//���j���[���e
		NULL
	);

	//�E�B���h�E���쐬�o�������`�F�b�N
	if (!hWnd) {
		return E_FAIL;
	}

	//�E�B���h�E�̕\��
	Show();
	
	//�E�B���h�E�n���h���̍X�V
	UpdateWindow(hWnd);

	return true;
}

//�E�B���h�E�\��
void WindowManager::Show()
{
	//�w�肳�ꂽ�E�B���h�E�̕\����Ԃ�ݒ�
	//�W���̐ݒ�
	ShowWindow(hWnd, SW_SHOW);
}

//���b�Z�[�W���[�v
bool WindowManager::MessageHandling()
{
	HRESULT	hr;//�G���[�`�F�b�N�ϐ�

	DWORD dwExecLastTime = 0;//�O��
	DWORD dwCurrentTime = 0;//����
	//����\��ݒ�
	timeBeginPeriod(1);

	//DirectX11�̏�����
	hr = DirectX11Manager::GetInstance()->Init(hWnd);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("DirectX11���������s"),
			TEXT("���b�Z�[�W�{�b�N�X"), MB_OK);
		return false;
	}

	GameManager::GetInstance()->Init();
	do
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//�E�B���h�E���b�Z�[�W����
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{

			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{

				dwExecLastTime = dwCurrentTime;

				//CManager::Update();//�}�l�[�W���X�V

				//CManager::Draw();//�}�l�[�W���`��
					//�|���S���̐������@�̎w��(�`��̒��O)
				//����̓g���C�A���O�����X�g�ŕ`��
				//DirectX11Manager::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				DirectX11Manager::GetInstance()->DrawBegin();
				GameManager::GetInstance()->Update();
				GameManager::GetInstance()->Draw();
				DirectX11Manager::GetInstance()->DrawEnd();
			}
		}
	} while (msg.message != WM_QUIT);

	GameManager::GetInstance()->Uninit();
	DirectX11Manager::GetInstance()->AllRelease();

	//����\��߂�
	timeEndPeriod(1);

	return (int)msg.wParam;
}


