#pragma once

#include "Core.h";
#include "Events/Event.h"
#include "Window.h"

namespace Skull {

	class SKULL_API Application{

	public:
		Application();
		virtual ~Application(); // punem virtual pt momentul cand punem in Sandbox ce-i aici

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// to be defined in CLIENT
	Application* CreateApplication();
}

