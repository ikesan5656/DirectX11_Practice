#pragma once

//#include "../ImGui/imgui_impl_dx11.h"
//#include "../ImGui/imgui_impl_win32.h"

class ImGuiManager_DX11 {
private:

public:
	static ImGuiManager_DX11* GetInstance();
	void CreateDevice();
};