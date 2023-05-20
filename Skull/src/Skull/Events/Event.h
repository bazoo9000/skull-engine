#pragma once

//#include "Skull/Core.h"
#include "../Core.h"
#include "skpch.h"

namespace Skull {

	// momentan, eventurile o sa blocheze aplicatia si o sa fie executate

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved, // the classic window management
		AppTick, AppUpdate, AppRender,										  // maybe delete later
		KeyPressed, KeyReleased,											  // tastatura
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled	  // mouse
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication    = BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; } \
								virtual EventType GetEventType() { return GetStaticType(); } \
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class SKULL_API Event {
		friend class EventDispatcher;

	public:
		// trebuie implementate mai tarziu
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0; // for debug purpose
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }; // for debug purpose

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}

	protected:
		bool m_Handled = false; // daca eventul a avut loc SI a fost executat ce era de executat sau mai bine zis HAS BEEN HANDLED
	};

	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event) // nu stim ce event o sa primim asa ca ii luam adresa
			: m_Event(event){}

		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType) {
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