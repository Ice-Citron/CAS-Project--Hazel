#include "hzpch.h"

#include "Application.h"
#include "Hazel/Log.h"

#include <GLFW/glfw3.h>


namespace Hazel {

// Binding Comments
/*
-- std::bind is used when you want to pass around a function with some of its arguments already specified
   "this" specifies that the function should be called on the current instance of "Application"
   it essentially binds the function to the current instance, effectively creating a callback that can be passed around and invoked.

-- GLFW doesn't understand C++ member functions or classes, so you can't directly pass a member function pointer to GLFW. Instead, you provide 
   a free function or static method. However, by using std::bind, you can create a callable object that effectively "wraps" the member function 
   call, including the object instance (this) it should be called on. (basically linking the method to the object instance, else uncallable)

--  When the event occurs, GLFW calls a predefined callback function.Inside this callback, you retrieve the bound callable from the user pointer 
   and call it with the event.The EventCallback function then invokes OnEvent on the Application instance.
*/
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1) 

	//In C++, the superclass constructor is invoked. Whenever a subclass constructor is invoked during an instantiation.
	Application::Application() {

		m_Window = std::unique_ptr<Window>(Window::Create());

		// SetEventCallback() sets the std::function<void(Event&)> attribute that m_Data.EventCallback is holding.
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent)); 
	}

	Application::~Application() {}

	// This is the method that's invoked in the lambda functions of GLFW methods for events, such as { glfwSetWindowCloseCallback, glfwSetKeyCallback, etc. }
	void Application::OnEvent(Event& e) {

		// Sets m_Event of EventDispatcher class as Event "e"
		EventDispatcher dispatcher(e); 
		
		// The Dispatch method checks if the passed event (m_Event) matches the type specified in the template parameter.If it does, it calls the provided 
		// function (parameter of type EventFN<T> func).
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		HZ_CORE_TRACE("{0}", e);
	}

	void Application::Run() {
		
		while (m_Running) {

			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate(); // This processes the event queue, and then triggers any callbacks that have been setted. 
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {

		m_Running = false;
		return true;
	}
}