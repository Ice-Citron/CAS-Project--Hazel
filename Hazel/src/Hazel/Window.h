#pragma once

#include "hzpch.h"

#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel {


	struct WindowProps {
		
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Hazel Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{}
	};


	// Interface (pure virtual methods) representing a desktop system (MacOS, Linux, Windows) based Window
	// Because these methods needs to be implemented to each specific desktop platforms
	class HAZEL_API Window {
	
	public:

		using EventCallbackFn = std::function<void(Event&)>; // std::function object, which: returns void, takes in a reference to Event object

		virtual ~Window() {}
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes (Accessors && Mutators)
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps()); // will be implemented for each specific platforms, in the directory "/platform/~~~"
	};

}