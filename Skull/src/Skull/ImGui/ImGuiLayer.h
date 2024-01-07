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

namespace Skull 
{
	class SKULL_API ImGuiLayer : public Layer 
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAtach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		// Layer render on its own
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}