#include"WindowManager.h"
#include <crtdbg.h>
//ウィンドウ関連
#pragma comment(lib, "winmm.lib")
//==========================================================================
//定数宣言
//==========================================================================


//==========================================================================
//プロトタイプ宣言
//==========================================================================


//==========================================================================
//グローバル変数
//==========================================================================


//===========
//メイン関数
//===========
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ヒープメモリを確保
	/*int *pNumber = new int[3];
	pNumber[0] = 1;
	pNumber[1] = 2;
	pNumber[2] = 3;*/


	//ウィンドウクラスの設定
	WindowManager::GetInstance()->RegisterWindowClass(hInstance);

	//ウィンドウ生成
	WindowManager::GetInstance()->InitializeWindow(hInstance);

	//メッセージループ
	WindowManager::GetInstance()->MessageHandling(hInstance);

	return 0;
}



