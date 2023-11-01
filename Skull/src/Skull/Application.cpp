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

		// merge de la -1 la 1 pe toate axele! (sau va fi convertit acolo)
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f, // A
			0.5f, -0.5f, 0.0f,  // B
			0.0f, 0.5f, 0.0f    // C
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		// asta traduce ce am trimis mai sus in ceva ce intelege GPU-ul
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr); // (index, cate vertex-uri, ce tip is, isNormalized?, cati bytes sunt intre vertex-uri, pointerul sau offset-ul (default ii 0))
	
		unsigned int indices[3] = { 0, 1, 2 }; // merge si short
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		// Behold, a new string trick!

		// This handles position of vertices
		std::string vertexSrc = R"( 
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main(){
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		// This handles color
		std::string fragmentSrc = R"( 
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main(){
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)"; // vec4(r, g, b, a) sau vec4(vec3, a)
		
		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
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

			m_Shader->Bind(); // in opengl nu conteaza ordinea la shader, dar la restu da si trebuie Bind sa fie prima chestie
			glBindVertexArray(m_VertexArray); // already binded, dar nu strica sal apelezi din nou
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr); // draw indices

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