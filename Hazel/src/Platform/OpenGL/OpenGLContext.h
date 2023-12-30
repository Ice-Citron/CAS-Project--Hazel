#pragma once

#include "Hazel/Renderer/GraphicsContext.h"


struct GLFWwindow;

namespace Hazel {

	class OpenGLContext : public GraphicsContext{

	public:

		OpenGLContext(GLFWwindow* m_WindowHandle);
		~OpenGLContext();

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:

		GLFWwindow* m_WindowHandle;
	};
}

// Archive from first 26 episodes. Comments on initialising an OpenGL window, through GLFW
/*
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

			//Context and glfwMakeContextCurrent() comments
			/*
			-- An OpenGL context is an environment which stores all of the data related to the state of the OpenGL environment. When you're using OpenGL to render graphics, 
			-- the context holds information about things like:
				** Which objects(like textures, buffers, etc.) are currently in use.
				** The current rendering states(like which shaders are active, what is the current color, etc.).
				** Configuration settings that control how OpenGL should perform rendering.
			-- OpenGL is designed to be platform - agnostic, which means it doesn't deal directly with the operating system or the window where the graphics are displayed. 
			-- Instead, it relies on a context that serves as a bridge between OpenGL's own environment and the actual display window managed by the operating system.

			-- The reason you need to make a context current is because without it, OpenGL wouldn't know where to send the rendered output, and
			-- it wouldn't have access to the resources it needs to perform rendering.
		
	glfwMakeContextCurrent(m_Window);


			// --------GLAD initialisation-------- 
			/*
			-- "gladLoadGLLoader" initialises GLAD, the OpenGL loader library. This is necessary for accessing modern OpenGL functions. it is a
			   function provided by GLAD to load OpenGL function pointers.
			-- It requires a function pointer as an argument, which is responsible for returning the address of OpenGL functions.
			-- 'glfwGetProcAddress' is a GLFW function that returns the address of an OpenGL function given its name.
			-- However, in this context, we are not calling 'glfwGetProcAddress' directly. Instead, we pass its pointer to 'gladLoadGLLoader'.
			-- This allows GLAD to use GLFW's mechanism to retrieve the addresses of OpenGL functions dynamically at runtime.
			-- The function pointers are essential for OpenGL to function correctly as they provide access to modern OpenGL features.

			** Long story short, this now allows GLFW to directly call openGL functions through GLAD.

	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	HZ_CORE_ASSERT(status, "Failed to initialise Glad!");


			// The purpose of UserPointer: allows you to associate a pointer to any user-defined data with the window. This can be a pointer to a 
			// class, a structure, or any other type of data you want to associate with that window.
	glfwSetWindowUserPointer(m_Window, &m_Data); // passing the struct "WindowData"
	SetVSync(true);
*/

// Archive from first 26 episodes. Comments on old WindowsWindow::OnUpdate() method. --	Comments on threading, swap buffers, poll events
/*
	void WindowsWindow::OnUpdate() {		// Poll Events, swaps buffer. Ran once per frame.

				// Polling for Events:	Continuously checking if there are any events from the operating system, like keyboard presses, mouse
				//						movements, window resizes, etc.
				// Event Queue:			When an event occurs, it gets placed into an event queue.
				// Event Processing:	On each iteration of your application's main loop, you typically call a function like glfwPollEvents() or glfwWaitEvents(),
				//						which processes this queue, triggering the callbacks that you've set for different events.
				// When an event is detected, the predefined callback function will be called, which calls data.EventCallback(event) -- (which is
				// Application::OnEvent() function) and thus leads to the EventDispatcher class, which enables the event to be called by their handle overall.

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

				// "glfwSwapBuffers" is a crucial part of double-buffered rendering, which is used to prevent flickering and tearing artifacts in animated graphics.
		glfwSwapBuffers(m_Window); 
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

