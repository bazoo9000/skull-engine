#pragma once

#include "Skull/Core.h"
#include "Layer.h"

#include <vector>

namespace Skull
{
	class SKULL_API LayerStack // s-ar putea sa punem elementele pe la mijlocul stack-ului deci nu-i neaparat un stack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	
	protected:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}