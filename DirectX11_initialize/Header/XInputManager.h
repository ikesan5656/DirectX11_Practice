#pragma once
#include <Windows.h>
#pragma comment(lib, "xinput.lib")
/*XInputのAPIをラップした管理クラス*/
#include <xinput.h>	//操作系
class XinputManager
{

private:
	//XINPUT_STATE state;
	//キーボードのキー
	int iKeyA = 0, iKeyD = 0, iKeyW = 0, iKeyS = 0;
	//ゲームパッドのボタン
	int iPad_left = 0, iPad_right = 0, iPad_up = 0, iPad_down = 0;
	int iPad_leftshoulder = 0, iPad_rightshoulder = 0;
	int iPad_A = 0, iPad_B = 0, iPad_X = 0, iPad_Y = 0;
public:
	static XinputManager* GetInstance();
	void Init();
	void Update();
	int GetKeyA();
};