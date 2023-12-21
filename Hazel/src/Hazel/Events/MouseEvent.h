#pragma once

#include "Event.h"


namespace Hazel {


	class HAZEL_API MouseMovedEvent : public Event {

	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y)
		{}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }
		
		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		//Macro, to declare the specific getters for MouseMovedEvent class
		EVENT_CLASS_TYPE(MouseMoved)
		//Macro, to declare category flag of keyEvent class [0b01010]
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY;
	};


	class HAZEL_API MouseScrolledEvent : public Event {

	public:

		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset)
		{}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		//Macro, to declare the specific getters for MouseScrolledEvent class
		EVENT_CLASS_TYPE(MouseScrolled)
		//Macro, to declare category flag of MouseScrolledEvent class [0b01010]
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_XOffset, m_YOffset;
	};


	class HAZEL_API MouseButtonEvent : public Event {

	public:

		inline int GetMouseButton() const { return m_Button; }
		//Macro, to declare category flag of MouseButtonEvent class [0b01010]
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:

		//protected constructor, meaning this class can only be instantiated by its children classes
		MouseButtonEvent(int button)
			: m_Button(button) 
		{}

		int m_Button;
	};


	class HAZEL_API MouseButtonPressedEvent : public MouseButtonEvent {

	public:

		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) //initialising superclass
		{}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		//Macro, to declare the specific getters for MouseButtonPressedEvent class
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	
	class HAZEL_API MouseButtonReleasedEvent : public MouseButtonEvent {
	
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) //initialising superclass
		{}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		//Macro, to declare the specific getters for MouseButtonReleasedEvent class
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}




