#pragma once

#include "Event.h"

namespace Skull 
{
	class SKULL_API KeyEvent : public Event
	{
	protected:
		int m_KeyCode;

	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}
	};

	class SKULL_API KeyPressedEvent : public KeyEvent 
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount){}

		inline int GetRepeatCount() const { return m_KeyCode; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);

	private:
		int m_RepeatCount;

	};

	class SKULL_API KeyReleasedEvent : public KeyEvent 
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		inline int GetRepeatCount() const { return m_KeyCode; }

		std::string ToString() const override 
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);;
	};

	class SKULL_API KeyTypedEvent : public KeyEvent 
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		inline int GetRepeatCount() const { return m_KeyCode; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped);

	private:
		int m_RepeatCount;

	};
}