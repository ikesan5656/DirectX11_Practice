#include "DirectInputManager.h"

//�V���O���g���C���X�^���X�擾
DirectInputManager* DirectInputManager::GetInstance() {
	static DirectInputManager self;
	return &self;
}

//���͏����̏�����
HRESULT DirectInputManager::InitInput(HINSTANCE hInstance, HWND hWnd)
{
	UNREFERENCED_PARAMETER(hWnd);

	if (m_pInput == NULL)
	{
		// DirectInput�I�u�W�F�N�g�̍쐬
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//���͏����̏I������
void DirectInputManager::UninitInput(void)
{
	if (m_pInput != NULL)
	{// DirectInput�I�u�W�F�N�g�̊J��
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//���͏����̍X�V����
void DirectInputManager::UpdateInput(void)
{
}

//�L�[�{�[�h�̏�����
HRESULT DirectInputManager::InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// ���͏����̏�����
	if (FAILED(InitInput(hInstance, hWnd)))
	{
		MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�̍쐬�Ɏ��s", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�o�C�X�̍쐬
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "�L�[�{�[�h������܂���", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h) �����厖
	if (FAILED(m_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevKeyboard->Acquire();

	return S_OK;
}

//�L�[�{�[�h�̏I������
void DirectInputManager::UninitKeyboard(void)
{
	if (m_pDevKeyboard != NULL)
	{// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
		// �L�[�{�[�h�ւ̃A�N�Z�X�����J��(���͐���I��)
		m_pDevKeyboard->Unacquire();

		m_pDevKeyboard->Release();
		m_pDevKeyboard = NULL;
	}

	// ���͏����̏I������
	UninitInput();
}

//�L�[�{�[�h�̍X�V����
void DirectInputManager::UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	// �f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
       
			m_aKeyStateTrigger[nCnKey] = (m_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];

			m_aKeyStateRelease[nCnKey] = (m_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & ~aKeyState[nCnKey];

			// �L�[���s�[�g���𐶐�
			if (aKeyState[nCnKey])
			{
				if (m_aKeyStateRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT)
				{
					m_aKeyStateRepeatCnt[nCnKey]++;
					if (m_aKeyStateRepeatCnt[nCnKey] == 1
						|| m_aKeyStateRepeatCnt[nCnKey] >= LIMIT_COUNT_REPEAT)
					{// �L�[�������n�߂��ŏ��̃t���[���A�܂��͈�莞�Ԍo�߂�����L�[���s�[�g���ON
						m_aKeyStateRepeat[nCnKey] = aKeyState[nCnKey];
					}
					else
					{
						m_aKeyStateRepeat[nCnKey] = 0;
					}
				}
			}
			else
			{
				m_aKeyStateRepeatCnt[nCnKey] = 0;
				m_aKeyStateRepeat[nCnKey] = 0;
			}

			// �L�[�v���X����ۑ�
			m_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		m_pDevKeyboard->Acquire();
	}
}

//�L�[�{�[�h�̃v���X��Ԃ��擾
bool DirectInputManager::GetKeyboardPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//�L�[�{�[�h�̃g���K�[��Ԃ��擾
bool DirectInputManager::GetKeyboardTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//�L�[�{�[�h�̃��s�[�g��Ԃ��擾
bool DirectInputManager::GetKeyboardRepeat(int nKey)
{
	return (m_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}

//�L�[�{�[�h�̃����[�X��Ԃ��擾
bool DirectInputManager::GetKeyboardRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
