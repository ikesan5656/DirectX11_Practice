/**
 * @file WindowManager.h
 * @brief ウィンドウの管理クラス(シングルトン)
 * @author 池ノ谷 優太
 * @date 2020/02/05
 */

#pragma once

#include<Windows.h>

//==========================================================================
//定数宣言
//==========================================================================
//クラス名
#define CLASS_NAME "DirectX11 Template"
#define WINDOW_NAME "DeferredRenderer"//ウィンドウ名
//スクリーンの縦横幅
//#define SCREEN_WIDTH	(1280)
//#define SCREEN_HEIGHT	(720)

#define SCREEN_WIDTH	(1920)
#define SCREEN_HEIGHT	(1080)


/**
* @brief ウィンドウの管理クラス
* @details 今のところ1つしか存在しないものなのでシングルトン
*/
class WindowManager

{
private:
	//ウィンドウハンドル
	HWND hWnd;
	//メッセージ
	MSG msg;

	//デスクトップのクライアント領域のサイズを保存する構造体変数。
	RECT DrawRectBaseCalcPos;


public:
	//デストラクタ
	~WindowManager();

	//シングルトンインスタンスの取得
	static WindowManager* GetInstance();


	//メッセージプロシージャはstatic
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//ウィンドウクラスの設定
	void RegisterWindowClass(HINSTANCE hInstance);

	//ウィンドウ生成
	bool InitializeWindow(HINSTANCE hInstance);

	//ウィンドウ表示
	void Show();

	//メッセージループ
	bool MessageHandling(HINSTANCE hInstance);

	RECT GetRC()
	{
		return DrawRectBaseCalcPos;
	}


};
