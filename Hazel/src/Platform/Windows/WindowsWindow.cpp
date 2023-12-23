#include "hzpch.h"
#include "WindowsWindow.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"


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

		//Context and glfwMakeContextCurrent() comments
		/*
		-- An OpenGL context is an environment which stores all of the data related to the state of the OpenGL environment. When you're using OpenGL to render graphics, the 
		-- context holds information about things like:
			** Which objects(like textures, buffers, etc.) are currently in use.
			** The current rendering states(like which shaders are active, what is the current color, etc.).
			** Configuration settings that control how OpenGL should perform rendering.
		-- OpenGL is designed to be platform - agnostic, which means it doesn't deal directly with the operating system or the window where the graphics are displayed. Instead, it relies on a 
		-- context that serves as a bridge between OpenGL's own environment and the actual display window managed by the operating system.

		-- The reason you need to make a context current is because without it, OpenGL wouldn't know where to send the rendered output, and 
		-- it wouldn't have access to the resources it needs to perform rendering.
		*/
		glfwMakeContextCurrent(m_Window); 

		// The purpose of UserPointer: allows you to associate a pointer to any user-defined data with the window. This can be a pointer to a 
		// class, a structure, or any other type of data you want to associate with that window.
		glfwSetWindowUserPointer(m_Window, &m_Data); // passing the struct "WindowData"
		SetVSync(true);


		// ---------------------------------------------------------------------------------------------------
		// Setting GLFW Callbacks 
		// callbacks for various window events are set using lambda functions that capture the WindowData context and create the appropriate event, invoking EventCallback.
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
					keyReleasedEvent event(key);
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
		glfwPollEvents(); 


		// [Double Buffering] In the context of graphics, "buffer" generally refers to a block of memory used for storing image data. In double-buffered rendering, 
		// there are two buffers associated with a window:
			// Front Buffer: The buffer currently being displayed on the screen.
			// Back Buffer:  The buffer where the next frame is being drawn.
		// When you're rendering a frame, you draw to the back buffer. Once you're done drawing the entire frame, you call glfwSwapBuffers. This function swaps the 
		// back buffer with the front buffer, effectively displaying your newly rendered frame on the screen. The buffer that was the front buffer becomes the back 
		// buffer for the next frame, and you start drawing the next frame onto it.
			// The main reason for double buffering is to provide a smooth visual experience. If you were to draw directly to the front buffer, the user 
			// might see the frame being drawn piece by piece, resulting in flickering.
		glfwSwapBuffers(m_Window); // "glfwSwapBuffers" is a crucial part of double-buffered rendering, which is used to prevent flickering and tearing artifacts in animated graphics.
	}

	// ---------------------------------------------------------------Comments on Threading [Context and Buffers]---------------------------------------------------------------
	/*
	-- glfwSwapBuffers is thread-safe, meaning it can be called from any thread. However, if you're using OpenGL or OpenGL ES, the context associated with the window you're swapping 
	   buffers for must be current on the calling thread, as OpenGL contexts are thread-specific.
	   
	-- Why contexts are neccesary: OpenGL is designed as an environment. Each operation you perform with OpenGL changes its state. For example, when you bind a texture or set a 
	   viewport size, you're changing the state of the OpenGL context. These changes remain in effect until they are changed again. A context in OpenGL is an abstract concept that
	   represents the state of all the OpenGL state variables. This context holds the state of the OpenGL pipeline, including textures, shaders, buffer objects, and various settings 
	   that control how rendering is performed. When you perform operations in OpenGL, you're actually modifying or querying the state of the current context.

	-- Thread specific nature of contexts: The thread-specific nature of OpenGL contexts comes from how operating systems and graphics drivers are 
	   designed to handle rendering operations:
		** Exclusive Access: Rendering commands for a particular context must be issued from a single thread to ensure that the state is modified and queried in a consistent, predictable way.
		** Concurrency Issues: If multiple threads could access the same context simultaneously, it would lead to race conditions and inconsistencies, as OpenGL's state is not inherently 
		   designed for concurrent access.
		** Graphics Drivers: Most graphics drivers are not thread-safe because they are designed with the assumption that they will be accessed by a single thread at a time for a given context.
	
	-- How contexts are used in multi-threading:
		** Single Context, Multiple Threads: You can create a single OpenGL context and make it current on different threads at different times. However, only one thread can use the context at 
		   any given moment, and you must ensure proper synchronization when switching the context between threads.
		** Multiple Contexts: You can create a separate OpenGL context for each thread. In this case, each context has its own state, and threads can render independently. However, sharing 
		   resources between contexts can be complex and is limited by the capabilities provided by OpenGL and the graphics driver.

		** It's also worth noting that modern graphics APIs like Vulkan have been designed with multithreading in mind, allowing for a more granular control over synchronization and state, 
		   making them more suitable for high-performance, multithreaded applications than OpenGL.
	
	*/

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