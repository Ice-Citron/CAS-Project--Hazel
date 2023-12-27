#include "hzpch.h"
#include "WindowsInput.h"

#include "Hazel/Application.h"
#include <GLFW/glfw3.h>


namespace Hazel {

	// WindowsInput() is casted to (Input*) since it is a subclass afterall.
	// Overall, this enables the WindowsInput class' (platform-specific) methods to be callable with just using the Input class alone, without
	// having to specifically declare which platform/OS that's being useds
	Input* Input::s_Instance = new WindowsInput(); 

	bool WindowsInput::IsKeyPressedImpl(int keycode) const {
		
		// As of EP19, Window.h has been given an accessor to provide m_Window(or the GLFWwindow pointer).
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT; // asks GLFW is the key is pressed or repeatedly pressed (held down)
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button) const {

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl() const
	{

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return std::pair<float, float>(xpos, ypos);
	}

	float WindowsInput::GetMouseXImpl() const {
		
		auto[x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl() const {
		
		auto[x, y] = GetMousePositionImpl();
		return y;
	}

}