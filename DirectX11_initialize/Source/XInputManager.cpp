#include "XInputManager.h"
#include <WinUser.h>//ユーザ向け関数の宣言

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
	//キーボード更新(xinputではない)
	if (GetAsyncKeyState('A') & 0x8000) iKeyA = 1;
	if (GetAsyncKeyState('D') & 0x8000) iKeyD = 1;
	if (GetAsyncKeyState('W') & 0x8000) iKeyW = 1;
	if (GetAsyncKeyState('S') & 0x8000) iKeyS = 1;

	//指定されたコントローラーの現在の状態を取得します。
	//第一引数はどのコントローラか、第二はXINPUT_STATE構造体へのポインタ
	//XInputGetState(0, &state);
}

int XinputManager::GetKeyA() {
	return iKeyA;
}