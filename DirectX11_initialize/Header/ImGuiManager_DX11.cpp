#include "ImGuiManager_DX11.h"

//#include "../ImGui/imgui.h"
//#include "../ImGui/imgui_impl_dx11.h"
ImGuiManager_DX11* ImGuiManager_DX11::GetInstance() {
	static ImGuiManager_DX11 self;
	return &self;
}

void ImGuiManager_DX11::CreateDevice()
{
	//�f�o�C�X�̍쐬�E�j�����s��ꂽ��InvalidateDeviceObjects(),CreateDeviceObjects()���R�[�����܂�
	//ImGui_ImplDX11_InvalidateDeviceObjects();
	//ImGui_ImplDX11_CreateDeviceObjects();
}
