#include "XInputManager.h"
#include <WinUser.h>//���[�U�����֐��̐錾

XinputManager* XinputManager::GetInstance() {
	static XinputManager self;
	return &self;
}

void XinputManager::Init()
{
	iKeyA = 0, iKeyD = 0, iKeyW = 0, iKeyS = 0;
}

void XinputManager::Update()
{
	iKeyA = 0, iKeyD = 0, iKeyW = 0, iKeyS = 0;
	//�L�[�{�[�h�X�V(xinput�ł͂Ȃ�)
	if (GetAsyncKeyState('A') & 0x8000) iKeyA = 1;
	if (GetAsyncKeyState('D') & 0x8000) iKeyD = 1;
	if (GetAsyncKeyState('W') & 0x8000) iKeyW = 1;
	if (GetAsyncKeyState('S') & 0x8000) iKeyS = 1;

	//�w�肳�ꂽ�R���g���[���[�̌��݂̏�Ԃ��擾���܂��B
	//�������͂ǂ̃R���g���[�����A����XINPUT_STATE�\���̂ւ̃|�C���^
	//XInputGetState(0, &state);
}

int XinputManager::GetKeyA() {
	return iKeyA;
}