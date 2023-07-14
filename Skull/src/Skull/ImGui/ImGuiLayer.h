#pragma once

#include "Skull/Layer.h"

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
		float m_Time = 0.0f;
	};
}