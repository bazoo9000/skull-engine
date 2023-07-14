#include "skpch.h"
#include "Application.h"

#include "Skull/Log.h"

#include <glad/glad.h>

namespace Skull {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		SK_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent)); // cred ca ar fi mai bine Application::OnEvent
	}

	Application::~Application() {
		// nimic
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAtach();
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAtach();
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose)); // ce se afla in < Aici > este pt T::GetStaticType()

		// SK_CORE_TRACE("{0}", e); // DEBUG, sa vedem ce event a avut loc

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled) {
				break; // daca 
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false; // oprim while-ul din Run()
		return true; // HANDLED
	}

	void Application::Run() {

		while (m_Running) {
			glClearColor(1, 1, 1, 1); // flashbang 
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}
}