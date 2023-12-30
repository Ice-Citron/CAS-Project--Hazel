#include "hzpch.h"
#include "WindowsWindow.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"


namespace Hazel {

	// boolean to keep track whether has GLFW been initialised. To ensure that Init() is only called once.
	static bool s_GLFWInitialized = false;

	//Called by GLFW when an error occurs. Which is then logged. 
	static void GLFWErrorCallback(int error, const char* description) {
		HZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props) { // props is a default parameter
		// returns the Window application created, and the pointer is stored as unique_ptr, in Application.cpp class
		return new WindowsWindow(props);
	}
	
	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props) {

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
		
		if (!s_GLFWInitialized) { // initialised GLFWa if it hasn't beena already

			// TODO: glfwTerminate on system shutdown
			int success = glfwInit(); 
			HZ_CORE_ASSERT(success, "Could not intialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		//Creates a new GLFW window
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();
		

		

		// The purpose of UserPointer: allows you to associate a pointer to any user-defined data with the window. This can be a pointer to a 
		// class, a structure, or any other type of data you want to associate with that window.
		glfwSetWindowUserPointer(m_Window, &m_Data); // passing the struct "WindowData"
		SetVSync(true);




		// ---------------------------------------------------------------------can delete up to here.----------------------------------------------------------------------------

		// ---------------------------------------------------------------------------------------------------
		// Setting GLFW Callbacks 
		// callbacks for various window events are set using lambda functions that capture the WindowData context and create the appropriate event, invoking EventCallback.
		/*
		-- m_Window is passed into glfwSetCharCallback(as an example) as which handle will it set this CharCallback to. 
		-- This lambda function, or cbfun, will then be a pointer that is set to the m_Window class. (note: m_Window is a GLFWwindow object).
		-- So from now on, whenever a specific event is detected, this lambda function will be called by the GLFWwindow object. 
		*/
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
		
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {

				case (GLFW_PRESS): {
				
					KeyPressedEvent event(key, 0); 
					data.EventCallback(event);
					break;
				}
				case (GLFW_RELEASE): {
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case (GLFW_REPEAT): {
					KeyPressedEvent event(key, 1); 
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
			
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {

				case (GLFW_PRESS): {
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case (GLFW_RELEASE): {
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() { // Poll Events, swaps buffer. Ran once per frame. 

		// Polling for Events:	Continuously checking if there are any events from the operating system, like keyboard presses, mouse 
		//						movements, window resizes, etc.
		// Event Queue:			When an event occurs, it gets placed into an event queue.
		// Event Processing:	On each iteration of your application's main loop, you typically call a function like glfwPollEvents() or glfwWaitEvents(), 
		//						which processes this queue, triggering the callbacks that you've set for different events.
		// When an event is detected, the predefined callback function will be called, which calls data.EventCallback(event) -- (which is 
		// Application::OnEvent() function) and thus leads to the EventDispatcher class, which enables the event to be called by their handle overall. 
		glfwPollEvents();

		m_Context->SwapBuffers();
	}
	

	// VSYNC, short for Vertical Synchronization, is a display technology used to prevent screen tearing in graphics-intensive applications. 
	// It works by synchronizing the frame rate of your computer's graphics card with the refresh rate of your monitor.
	void WindowsWindow::SetVSync(bool enabled) {

		// When VSync is enabled with a swap interval of 1, glfwSwapBuffers will synchronize the swap to the vertical refresh rate of the display, which prevents 
		// tearing (where part of one frame and part of another are displayed at the same time). A swap interval greater than 1 would wait multiple refresh cycles, 
		// effectively reducing the frame rate.
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return m_Data.VSync;
	}

}

// Difference between GLFW and GLAD
/*
-- GLAD vs. GLFW: GLAD is a loader for OpenGL functions, allowing access to modern OpenGL features. GLFW, on the other hand, is used for creating 
   windows, OpenGL contexts, and managing inputs.

-- Complementary Usage: In modern OpenGL development, both GLAD and GLFW are used together but for different aspects of the graphics pipeline. 
   GLAD handles the loading of OpenGL functions, while GLFW deals with window and input management.
*/