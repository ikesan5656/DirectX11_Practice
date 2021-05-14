#pragma once
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <Windows.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
//マクロ定義
#define	NUM_KEY_MAX			(256)	// キーの最大数
#define	LIMIT_COUNT_REPEAT	(20)	// リピートカウントリミッター

class DirectInputManager {
private:
	LPDIRECTINPUT8			m_pInput = NULL;					// DirectInputオブジェクトへのポインタ
	LPDIRECTINPUTDEVICE8	m_pDevKeyboard = NULL;				// 入力デバイス(キーボード)へのポインタ
	BYTE					m_aKeyState[NUM_KEY_MAX];			// キーボードの入力情報ワーク
	BYTE					m_aKeyStateTrigger[NUM_KEY_MAX];	// キーボードのトリガー情報ワーク
	BYTE					m_aKeyStateRelease[NUM_KEY_MAX];	// キーボードのリリース情報ワーク
	BYTE					m_aKeyStateRepeat[NUM_KEY_MAX];		// キーボードのリピート情報ワーク
	int						m_aKeyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ

	HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);
	void UninitInput(void);
	void UpdateInput(void);
public:
	static DirectInputManager* GetInstance();

	HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
	void UninitKeyboard(void);
	void UpdateKeyboard(void);

	bool GetKeyboardPress(int nKey);
	bool GetKeyboardTrigger(int nKey);
	bool GetKeyboardRepeat(int nKey);
	bool GetKeyboardRelease(int nKey);
};