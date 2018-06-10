#include "SystemUI.h"

#include "SystemManager.h"
#include "Window.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl_gl3.h"

namespace Core {

	SystemUI::SystemUI() : System(SystemType::UI)
	{
	}

	SystemUI::~SystemUI()
	{
	}
	bool SystemUI::Init()
	{
		// Setup Dear ImGui binding
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
		ImGui_ImplSdlGL3_Init(SystemManager::GetInstance().GetSystem<Core::Window>()->GetWindow());

		// Setup style
		ImGui::StyleColorsDark();


		return true;
	}
	void SystemUI::Update()
	{
		ImGui_ImplSdlGL3_NewFrame(SystemManager::GetInstance().GetSystem<Core::Window>()->GetWindow());
	}
	void SystemUI::Render()
	{
		ImGui::Render();
		ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());//To display GUI
	}
	bool SystemUI::Shutdown()
	{
		return true;
	}
}
