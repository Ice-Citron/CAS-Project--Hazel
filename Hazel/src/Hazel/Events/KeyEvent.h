#pragma once

#include "Event.h"


namespace Hazel {

	class HAZEL_API KeyEvent : public Event {

	public:

		inline int GetKeyCode() const { return m_KeyCode; }
		//Macro, to declare category flag of keyEvent class [0b00110]
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:

		//protected constructor, meaning this class can only be instantiated by its children classes
		KeyEvent(int keyCode) 
			: m_KeyCode(keyCode)
		{}
		int m_KeyCode;
	};


	class HAZEL_API KeyPressedEvent : public KeyEvent {

	public:

		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), m_RepeatCount(repeatCount)
		{}

		inline int GetRepeatCount() const { return m_RepeatCount; }
		
		// Redacted - no longer needed
		/*
		// Added myself, getter method for m_GLFWwindow
		// Have been casted to int, so that KeyEvent.h don't need to import glfw3.h
		inline int* GetGLFWwindow() const { return m_GLFWwindow; } 
		*/

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}
		
		//Macro, to declare the specific getters for keyPressedEvent class
		EVENT_CLASS_TYPE(KeyPressed)

	private:

		int m_RepeatCount;
		// Redacted - no longer needed
		/*
		// This has been added myself, contrary to Cherno's version, because there's no way to get the modifier key's current 
		// state without using glfwGetKey() due to newer imGui version, and this method required pointer to the GLFWwindow object
		// int* m_GLFWwindow;
		*/
	};


	class HAZEL_API KeyReleasedEvent : public KeyEvent {

	public: 

		KeyReleasedEvent(int keyCode)
			: KeyEvent(keyCode) //initialising superclass
		{}

		std::string ToString() const override{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		//Macro, to declare the specific getters for keyReleasedEvent class
		EVENT_CLASS_TYPE(KeyReleased)
	};


	class HAZEL_API KeyTypedEvent : public KeyEvent {

	public:

		KeyTypedEvent(int keycode)
			: KeyEvent(keycode)
		{}

		std::string ToString() const override {

			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}