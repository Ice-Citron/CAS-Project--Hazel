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
			: KeyEvent(keyCode), m_RepeatCount(repeatCount) //initialising superclass
		{}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}
		
		//Macro, to declare the specific getters for keyPressedEvent class
		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};


	class HAZEL_API keyReleasedEvent : public KeyEvent {

	public: 
		keyReleasedEvent(int keyCode)
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

}