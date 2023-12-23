#pragma once

#include "hzpch.h"
#include "Hazel/Core.h"


namespace Hazel {

	// Events in Hazel are currently blocking, meaning when an event occurs it immeadiately gets dispatached and must be
	// dealth with right then an there. For the future, a better strategy might be to buffer events in an event bus and process
	// them during the "event" part of the update stage.

	enum class EventType { // scoped, more type safety, 
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved, 
		AppTick, AppUpdate, AppRender, 
		KeyPressed, KeyReleased, 
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	//left bitwise operator shit by ~
	enum EventCategory { // unscoped, less type safety, 
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


	//Pretty much an interface, which ass specfic event types will inherit. 
	class HAZEL_API Event {

	public:

		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;

		//used in ostream << override
		virtual std::string ToString() const { return GetName(); } 

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	};


	class EventDispatcher {
		// A utility class that's used to check if an event is of a particular type and dispatch it to a function that can handle that type. 
		// This is achieved through the Dispatch template method, which takes a templated EventFn function. 
		// If the event matches the template type T, the function is called with the event cast to that type.

		template<typename T>
		using EventFn = std::function<bool(T&)>;
		// EventFn is a std::function instance that returns bool, and takes in T& as parameter
		// T can be any EventType (check enum class)

	public:

		// This instance is created every single time OnEvent() is called, which exists in the platform-specific Windows class, such as "WindowsWindow"
		// which inherits the Window class, and exists in their WindowData class' EventCallback attribute.
		// Each time this EventCallback is called, OnEvent(Event& e) from Application class is called, resulting in a new EventDispatcher object
		// being created, which passes in the specific event that occur, and then multiple "Dispatch" methods will be checked against, and when true
		// a specific handler will be called,. such as "OnWindowClose(WindowCloseEvent& e)"
		EventDispatcher(Event& event) 
			: m_Event(event)
		{}

		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				// if the event that you are trying to dispatch matches with 
				// the parameter type (T&) of the std::Function
				// the code will then call the EventFn<T> func function, with the event passed as parameter
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:

		Event& m_Event;
	};


	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		// allows for easy logging of events, invokes the virtual method of .ToString()
		return os << e.ToString();
	}

}




