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
	//�f�o�C�X�̍쐬�E�j�����s��ꂽ��InvalidateDeviceObjects(),CreateDeviceObjects()���R�[�����܂�
	ImGui_ImplDX11_InvalidateDeviceObjects();
	ImGui_ImplDX11_CreateDeviceObjects();
}

void ImGuiManager_DX11::Init(HWND hWnd)
{
	m_bMainWindow = true;

	IMGUI_CHECKVERSION();//ImGui�̃o�[�W����
	ImGui::CreateContext();

	ImGui_ImplWin32_Init(hWnd);
	//ImGui����������
	ImGui_ImplDX11_Init(
		DirectX11Manager::GetInstance()->GetDevice(),
		DirectX11Manager::GetInstance()->GetContext());

	ImGui::StyleColorsClassic();
}

void ImGuiManager_DX11::Uninit()
{
	//ImGui�̉������
	ImGui_ImplDX11_Shutdown();
	//�R���e�L�X�g�̔j���A���b�Z�[�W�̔j��
	ImGui::DestroyContext();
}

void ImGuiManager_DX11::Update()
{
	//�K�����[�v�̍ŏ��ɌĂ�(�Ă΂Ȃ��ƃN���b�V��)
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager_DX11::Draw()
{
	//ImGui_ImplDX11_NewFrame();
	if (m_bMainWindow) {
		ImGui::SetNextWindowPos(ImVec2(50, 100), 2);//�E�B���h�E�|�W�V�����̃Z�b�g
		ImGui::SetNextWindowSize(ImVec2(400, 300), 2);//�E�B���h�E�T�C�Y�̃Z�b�g

		ImGui::Begin("Main Window", &m_bMainWindow);//1�Z�b�g�̕`��J�n�錾
		ImGui::Text("Orner:ikesan");
		ImGui::End();//1�Z�b�g�̕`��I���錾
	}

	ImGui::EndFrame();
	ImGui::Render();//�`�施��
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
