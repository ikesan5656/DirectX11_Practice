/**
 * @file WindowManager.cpp
 * @brief ウィンドウの管理
 * @author 池ノ谷 優太
 * @date 2020/02/05
 */
#include "WindowManager.h"
#include"DirectX11Manager.h"
#include"GameManager.h"
#include "DirectInputManager.h"

//#include "../ImGui/imgui_impl_win32.h"
#include "ImGuiManager_DX11.h"
//デストラクタ
WindowManager::~WindowManager()
{

}

//シングルトンインスタンスの取得
WindowManager * WindowManager::GetInstance()
{
	static WindowManager self;
	//自身を返す
	return &self;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);//ImGuiのプロシージャ
LRESULT CALLBACK WindowManager::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	#ifdef _DEBUG

	//ImGuiのプロシージャ
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
		return true;
	}

	#endif

	int nID;

	switch (uMsg)
	{

	case WM_SIZE:

		#ifdef _DEBUG
			ImGuiManager_DX11::GetInstance()->CreateDevice();
		#endif
				break;

	case WM_DESTROY:
		PostQuitMessage(0);//WM_QUITメッセージの送信
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{

		case VK_ESCAPE://[ESC]キーが押された

			#ifdef _DEBUG//デバッグ時すぐにアプリを閉じる
						PostQuitMessage(0);//WM_QUITメッセージの送信
			#endif

			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2);

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
	//ウィンドウクラスの設定
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),		//サイズ
		CS_CLASSDC,				//スタイル
		WindowManager::WndProc,				//プロシージャ関数
		0L,						//普段は使わない
		0L,						//普段は使わない
		hInstance,
		NULL,
		NULL,
		NULL,
		NULL,
		CLASS_NAME,	//ウィンドウクラスネーム
		NULL
	};

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);//ウィンドウクラスで登録
}

bool WindowManager::InitializeWindow(HINSTANCE hInstance)
{
	//ウィンドウサイズの指定
	RECT WindowRect = { (LONG)0, (LONG)0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
	//ウィンドウのスタイルを指定
	AdjustWindowRect(&WindowRect, WS_OVERLAPPEDWINDOW ^WS_MAXIMIZEBOX ^WS_THICKFRAME, false);

	//ウィンドウの非クライアント領域の幅と高さを考慮したクライアント領域の計算。
	int WindowWidth = WindowRect.right - WindowRect.left;
	int WindowHeight = WindowRect.bottom - WindowRect.top;

	////デスクトップのクライアント領域のサイズを保存する構造体変数。
	//RECT DrawRectBaseCalcPos;

	//デスクトップのクライアント領域(画面解像度)を取得する。
	GetWindowRect(GetDesktopWindow(), &DrawRectBaseCalcPos);

	//ウィンドウの中心座標がデスクトップの中心座標になるように、デスクトップ上でのウィンドウの左上生成座標を計算。
	int DrawRectPosX = ((DrawRectBaseCalcPos.right - DrawRectBaseCalcPos.left) - WindowWidth) / 2;
	int DrawRectPosY = ((DrawRectBaseCalcPos.bottom - DrawRectBaseCalcPos.top) - WindowHeight) / 2;

	
	//メインウィンドウの作成
	hWnd = CreateWindowEx(//ウィンドウ作成
		0,//ドラッグアンドドロップ
		CLASS_NAME,//クラス名
		WINDOW_NAME,//ウィンドウ名（タイトル）
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX /*| WS_VSCROLL*/,//デフォルトウィンドウスタイル
																			//WS_POPUP,
		//x,//ウィンドウ左上X座標
		//y,//ウィンドウ左上Y座標
		DrawRectPosX,
		DrawRectPosY + 16,
		WindowWidth,//幅
		WindowHeight,//高さ
		NULL,//親ウィンドウへのハンドル
		NULL,//メニューハンドル（内容）
		hInstance,//メニュー内容
		NULL
	);

	//ウィンドウが作成出来たかチェック
	if (!hWnd) {
		return E_FAIL;
	}

	//ウィンドウの表示
	Show();
	
	//ウィンドウハンドルの更新
	UpdateWindow(hWnd);

	return true;
}

//ウィンドウ表示
void WindowManager::Show()
{
	//指定されたウィンドウの表示状態を設定
	//標準の設定
	ShowWindow(hWnd, SW_SHOW);
}

//メッセージループ
bool WindowManager::MessageHandling(HINSTANCE hInstance)
{
	HRESULT	hr;//エラーチェック変数

	DWORD dwExecLastTime = 0;//前回
	DWORD dwCurrentTime = 0;//現在
	//分解能を設定
	timeBeginPeriod(1);

	//DirectX11の初期化
	hr = DirectX11Manager::GetInstance()->Init(hWnd);

	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("DirectX11初期化失敗"),
			TEXT("メッセージボックス"), MB_OK);
		return false;
	}

	//キーボード初期化
	DirectInputManager::GetInstance()->InitKeyboard(hInstance, hWnd);

	#ifdef _DEBUG
	ImGuiManager_DX11::GetInstance()->Init(hWnd);
	#endif

	GameManager::GetInstance()->Init();
	do
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//ウィンドウメッセージ処理
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{

			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{

				dwExecLastTime = dwCurrentTime;

				//CManager::Update();//マネージャ更新

				//CManager::Draw();//マネージャ描画
					//ポリゴンの生成方法の指定(描画の直前)
				//今回はトライアングルリストで描画
				//DirectX11Manager::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				
				DirectInputManager::GetInstance()->UpdateKeyboard();
				#ifdef _DEBUG
				ImGuiManager_DX11::GetInstance()->Update();
				#endif
				GameManager::GetInstance()->Update();

				DirectX11Manager::GetInstance()->DrawBegin();

				GameManager::GetInstance()->Draw();
				#ifdef _DEBUG
								ImGuiManager_DX11::GetInstance()->Draw();
				#endif
				DirectX11Manager::GetInstance()->DrawEnd();


			}
		}
	} while (msg.message != WM_QUIT);

	#ifdef _DEBUG
	ImGuiManager_DX11::GetInstance()->Uninit();
	#endif

	GameManager::GetInstance()->Uninit();
	DirectInputManager::GetInstance()->UninitKeyboard();
	DirectX11Manager::GetInstance()->AllRelease();

	//分解能を戻す
	timeEndPeriod(1);

	return (int)msg.wParam;
}


