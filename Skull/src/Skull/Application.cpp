#include "skpch.h"
#include "Application.h"

#include "Skull/Events/ApplicationEvent.h"
#include "Skull/Log.h"

namespace Skull {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {
		// nimic
	}

	void Application::Run() {

		while (m_Running) {
			m_Window->OnUpdate();
		}
	}
}