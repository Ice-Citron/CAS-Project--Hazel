#pragma once

#include "Hazel/Input.h"


namespace Hazel {

	class WindowsInput : public Input {

	protected:

		virtual bool IsKeyPressedImpl(int keycode) const override;

		virtual bool IsMouseButtonPressedImpl(int button) const override;
		virtual std::pair<float, float> GetMousePositionImpl() const override;
		virtual float GetMouseXImpl() const override;
		virtual float GetMouseYImpl() const override;

	};
}

// Platform specific files, such as this one "WindowsInput" and "WindowsWindow" are not declared with HAZEL_API (_declspec(dllexport))
// , which means that they are not exported in the Hazel DLL. Which means these classes are not directly accessible to external projects
// or applications, that links against the Hazel DLL. 

// Conversely, when a class is declared with the HAZEL_API, it ensures that the core functionalities are exported to the DLL, making them
// reusable across other projects (eg. Sandbox). 

// For now, (27/12/2023) I believe that these platform specific files, when not included in the DLL, will be instead compiled directly into
// the application, eg "Sandbox". This setup overalls enables a modular approach where the core engine functionalities are available via
// the DLL, whilst platform-specific implementations are compiled within the application. 

// This way, each build for the application contains only the relevant platform-specific code.
