#include "ImGuiManager_DX11.h"

//#include "../ImGui/imgui.h"
//#include "../ImGui/imgui_impl_dx11.h"
ImGuiManager_DX11* ImGuiManager_DX11::GetInstance() {
	static ImGuiManager_DX11 self;
	return &self;
}

void ImGuiManager_DX11::CreateDevice()
{
	//デバイスの作成・破棄が行われたらInvalidateDeviceObjects(),CreateDeviceObjects()をコールします
	//ImGui_ImplDX11_InvalidateDeviceObjects();
	//ImGui_ImplDX11_CreateDeviceObjects();
}
