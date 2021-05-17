#include "ImGuiManager_DX11.h"
#include "DirectX11Manager.h"
//#include "../ImGui/imgui.h"
//#include "../ImGui/imgui_impl_dx11.h"
ImGuiManager_DX11* ImGuiManager_DX11::GetInstance() {
	static ImGuiManager_DX11 self;
	return &self;
}

void ImGuiManager_DX11::CreateDevice()
{
	//デバイスの作成・破棄が行われたらInvalidateDeviceObjects(),CreateDeviceObjects()をコールします
	ImGui_ImplDX11_InvalidateDeviceObjects();
	ImGui_ImplDX11_CreateDeviceObjects();
}

void ImGuiManager_DX11::Init(HWND hWnd)
{
	m_bMainWindow = true;

	IMGUI_CHECKVERSION();//ImGuiのバージョン
	ImGui::CreateContext();

	ImGui_ImplWin32_Init(hWnd);
	//ImGui初期化処理
	ImGui_ImplDX11_Init(
		DirectX11Manager::GetInstance()->GetDevice(),
		DirectX11Manager::GetInstance()->GetContext());

	ImGui::StyleColorsClassic();
}

void ImGuiManager_DX11::Uninit()
{
	//ImGuiの解放処理
	ImGui_ImplDX11_Shutdown();
	//コンテキストの破棄、メッセージの破棄
	ImGui::DestroyContext();
}

void ImGuiManager_DX11::Update()
{
	//必ずループの最初に呼ぶ(呼ばないとクラッシュ)
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager_DX11::Draw()
{
	//ImGui_ImplDX11_NewFrame();
	if (m_bMainWindow) {
		ImGui::SetNextWindowPos(ImVec2(50, 100), 2);//ウィンドウポジションのセット
		ImGui::SetNextWindowSize(ImVec2(400, 300), 2);//ウィンドウサイズのセット

		ImGui::Begin("Main Window", &m_bMainWindow);//1セットの描画開始宣言
		ImGui::Text("Orner:ikesan");
		ImGui::End();//1セットの描画終了宣言
	}

	ImGui::EndFrame();
	ImGui::Render();//描画命令
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
