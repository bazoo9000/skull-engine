// O reprezentare ABSTRACTA a unui window
// si nui pasa de ce platforma folosim ceea ce este perfect cand il punem pe windows, mac, linux, etc
#pragma once

#include "skpch.h"
#include "Skull/Core.h"
#include "Skull/Events/Event.h"

namespace Skull {
	
	struct WindowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Skull Engine",
					unsigned int width = 1280,
					unsigned int height = 720)
					: Title(title), Width(width), Height(height)
		{
			// nimic
		}
	};

	// clasa asta este pur virtual
	// scopul ei este de a fi definita pe fiecare platforma
	// NOTE: doar desktop, deoarece android este diferit (lol)
	class SKULL_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps()); // asta ne va da un window pe o platforma anume
	};
}