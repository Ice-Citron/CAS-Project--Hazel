#include "hzpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "GLFW/glfw3.h"

#include "Hazel/Application.h"


namespace Hazel {

	ImGuiLayer::ImGuiLayer() 
		: Layer("ImGuiLayer")
	{}

	ImGuiLayer::~ImGuiLayer() {}

	void ImGuiLayer::OnAttach() {

		const char* glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		//IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		ImGui_ImplOpenGL3_Init(glsl_version);

	}

	void ImGuiLayer::OnDetach() {}

	// Like any other layer, this overriden method is called every frame/runloop, to update and render the ImGui interface.
	void ImGuiLayer::OnUpdate() {
	
		ImGuiIO& io = ImGui::GetIO(); // retrieves the ImGui IO structure

		// Application's window size is obtained, and set as display size for ImGui. This ensures that ImGui knows the dimensions that 
		// it has to work with for rendering. 
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		// Below calculates the time elapsed since last frame (DeltaTime). This is essential for animations and time-dependent operations in ImGui 
		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f); // If not yet initialised, assume 60 fps.
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame(); // Prepares the OpenGL3 renderer for a new ImGui frame. 
		ImGui::NewFrame(); // Signifies the start of a new ImGui frame. From here, you can start issuing commands to build the GUI for this new frame. 

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render(); // Finalises the ImGui frame. It processes all the commands issued since "ImGui::NewFrame()", and prepares render data. 
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Takes the prepared render data by ImGui, and renders it using the OpenGL3 backend. 
	}

	void ImGuiLayer::OnEvent(Event& event) {}
}