#pragma once

#include "Core.h";
#include "Events/Event.h"
#include "Window.h"

#include "Skull/Events/ApplicationEvent.h"

namespace Skull {

	class SKULL_API Application{

	public:
		Application();
		virtual ~Application(); // punem virtual pt momentul cand punem in Sandbox ce-i aici

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// to be defined in CLIENT
	Application* CreateApplication();
}

