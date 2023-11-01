#pragma once

#include "Core.h";

#include "Window.h"
#include "Skull/LayerStack.h"
#include "Skull/Events/Event.h"
#include "Skull/Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

#include "Renderer/Shader.h" // testing, delete later
#include "Renderer/Buffer.h"

namespace Skull {

	class SKULL_API Application{

	public:
		Application();
		virtual ~Application(); // punem virtual pt momentul cand punem in Sandbox ce-i aici

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	// to be defined in CLIENT
	Application* CreateApplication();
}

