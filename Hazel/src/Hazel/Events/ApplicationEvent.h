#pragma once

#include "Event.h"

#include <sstream>

namespace Hazel {

	class HAZEL_API WindowResizeEvent : public Event {

	public:

		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height)
		{}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		//Macro, to declare the specific getters for WindowResizeEvent class
		EVENT_CLASS_TYPE(WindowResize)
		//Macro, to declare category flag of WindowResizeEvent class [0b00001]
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:

		unsigned int m_Width, m_Height;
	};


	class HAZEL_API WindowCloseEvent : public Event {
		
	public:

		WindowCloseEvent() {} //default constructor

		//Macro, to declare the specific getters for WindowCloseEvent class
		EVENT_CLASS_TYPE(WindowClose)
		//Macro, to declare category flag of WindowCloseEvent class [0b00001]
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};


	class HAZEL_API AppTickEvent : public Event {
		
	public:

		AppTickEvent() {} //default constructor

		//Macro, to declare the specific getters for AppTickEvent class
		EVENT_CLASS_TYPE(AppUpdate)
		//Macro, to declare category flag of AppTickEvent class [0b00001]
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};


	class HAZEL_API AppRenderEvent : public Event {
		
	public:
		
		AppRenderEvent() {} //default constructor

		//Macro, to declare the specific getters for AppRenderEvent class
		EVENT_CLASS_TYPE(AppUpdate)
		//Macro, to declare category flag of AppRenderEvent class [0b00001]
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}