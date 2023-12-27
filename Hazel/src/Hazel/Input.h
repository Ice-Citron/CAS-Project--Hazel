#pragma once

#include "Hazel/Core.h"


namespace Hazel {

	class HAZEL_API Input {
	// This class is mainly an interface, and will be inherited by desktop-platform specific subclasses, eg Windows, MacOS, Linux
	public:

		// calls platform specific IsKeyPressedImpl, etc. inherited method?
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); } 

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static bool GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static bool GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:

		virtual bool IsKeyPressedImpl(int keycode) const = 0; // This function will be implemented on per-platform basis.

		virtual bool IsMouseButtonPressedImpl(int button) const = 0;
		virtual std::pair<float, float> GetMousePositionImpl() const = 0;
		virtual float GetMouseXImpl() const = 0;
		virtual float GetMouseYImpl() const = 0;

	private:
		
		static Input* s_Instance; // Input class is singleton for now. -- Static function, belongs to class. 
	};
}