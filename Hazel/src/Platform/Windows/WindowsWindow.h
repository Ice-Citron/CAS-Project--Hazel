#pragma once

#include "Hazel/Window.h"

#include <GLFW/glfw3.h>


namespace Hazel {

	//Contains implementation for Windows OS
	class WindowsWindow : public Window
	{
	public:

		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override; //Update GLFW, swaps buffer. Ran once per frame. 

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes (Accessors && Mutators)
		inline void SetEventCallback(const EventCallbackFn& callback) override { 
			// Sets the "EventCallback" std::function<void(Event&)> attribute in the WindowData struct
			m_Data.EventCallback = callback; 
		} 
		
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:

		GLFWwindow* m_Window;

		struct WindowData {
			// Groups windows specific data nicely, this struct will be passed, instead of the entire class. 
			// This struct is passed to the inherited Init() methods, in the invocation "glfwSetWindowUserPointer(m_Window, &m_Data);" 
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			// using EventCallbackFn = std::function<void(Event&)>; -- declared in superclass "Window"
			// Callbacks are typically used to handle events such as keyPresses, windowResize, Mousemovement, etc.
			EventCallbackFn EventCallback;		// This holds "void Application::OnEvent(Event& e);" from the Application class, for example.
		
		};

		WindowData m_Data;
	};

}