#pragma once

#include "Skull/Core.h"
#include "Skull/Events/Event.h"

namespace Skull 
{
	class SKULL_API Layer 
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAtach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}
	
		inline const std::string& GetName() const { return m_DebugName; }
	
	protected:
		std::string m_DebugName; // nu ar trebui sa aiba nume Layer-ul, dar la debug ii helpfull
	};
}