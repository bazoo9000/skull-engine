#pragma once

#include "Skull/Layer.h"

#include "Skull/Events/KeyEvent.h"
#include "Skull/Events/MouseEvent.h"
#include "Skull/Events/ApplicationEvent.h"

/* 
NOTE: Ar fi o idee sa facem propriu nostru gui de la zero, 
dar ar lua mult timp, asa ca o sal copiem :) (temporar).
opengl3 mai exact, neo facut toata treba.
*/

namespace Skull {

	class SKULL_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAtach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);
	private:
		// Mouse
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		// Tastatura
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		// Window
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;
	};
}