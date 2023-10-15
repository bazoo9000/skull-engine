#include "skpch.h"
#include "Application.h"

#include "Skull/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace Skull {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		SK_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent)); // cred ca ar fi mai bine Application::OnEvent

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// MAKE A TRIANGLE!

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		// merge de la -1 la 1 pe toate axele! (sau va fi convertit acolo)
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f, // A
			0.5f, -0.5f, 0.0f,  // B
			0.0f, 0.5f, 0.0f    // C
		};

		// traducere: ducem datele din vertices din CPU in GPU, STATIC_DRAW este desenat doar o data
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// asta traduce ce am trimis mai sus in ceva ce intelege GPU-ul
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr); // (index, cate vertex-uri, ce tip is, isNormalized?, cati bytes sunt intre vertex-uri, pointerul sau offset-ul (default ii 0))
	
		glGenBuffers(1, &m_IndexBuffer); // sau ElementBuffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indices[3] = { 0, 1, 2 }; // merge si short
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	Application::~Application() {
		// nimic
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
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
			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_VertexArray); // already binded, dar nu strica sal apelezi din nou
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr); // draw indices

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}
}