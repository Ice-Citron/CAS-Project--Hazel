#pragma once

#include "Hazel/Core.h"

#include <String>
#include <functional>


namespace Hazel {

	// Events in Hazel are currently blocking, meaning when an event occurs it immeadiately gets dispatached and must be
	// dealth with right then an there. For the future, a better strategy might be to buffer events in an event bus and process
	// them during the "event" part of the update stage.

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved, 
		AppTick, AppUpdate, AppRender, 
		KeyPressed, KeyReleased, 
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	//left bitwise operator shit by ~
	enum EventCategory {
		None = 0,
		EventCategoryApplication	= BIT(0), //0b00001
		EventCategoryInput			= BIT(1), //0b00010
		EventCategoryKeyboard		= BIT(2), //0b00100
		EventCategoryMouse			= BIT(3), //0b01000
		EventCategoryMouseButton	= BIT(4)  //0b10000
	};


#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


	class HAZEL_API Event {

		friend class EventDispatcher;

	public:

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}

	protected:

		bool m_Handled = false;
	};


	class EventDispatcher {
		
		template<typename T>
		using EventFn = std::function<bool(T&)>;
		// EventFn is a std::function instance that returns bool, and takes in T&
		// T can be any EventType

	public:

		EventDispatcher(Event& event) 
			: m_Event(event)
		{}

		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				// if the event that you are trying to dispatch matches with 
				// the parameter type (T&) of the std::Function
				// the code will then call the EventFn<T> function, with the event
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:

		Event& m_Event;
	};


	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}

}




