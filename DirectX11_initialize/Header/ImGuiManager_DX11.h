#pragma once

#include "../ImGui/imgui_impl_dx11.h"
#include "../ImGui/imgui_impl_win32.h"
#include <Windows.h>

class ImGuiManager_DX11 {
private:
	bool m_bMainWindow;	//メインウィンドウフラグ
public:
	static ImGuiManager_DX11* GetInstance();
	void CreateDevice();
	void Init(HWND hWnd);
	void Uninit();
	void Update();
	void Draw();
};