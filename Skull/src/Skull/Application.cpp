#include "skpch.h"
#include "Application.h"

#include "Skull/Log.h"

#include <GLFW/glfw3.h>

namespace Skull {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent)); // cred ca ar fi mai bine Application::OnEvent
	}

	Application::~Application() {
		// nimic
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose)); // ce se afla in < Aici > este pt T::GetStaticType()

		SK_CORE_TRACE("{0}", e); // DEBUG, sa vedem ce event a avut loc
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false; // oprim while-ul din Run()
		return true; // HANDLED
	}

	void Application::Run() {

		while (m_Running) {
			glClearColor(1, 1, 1, 1); // flashbang 
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}