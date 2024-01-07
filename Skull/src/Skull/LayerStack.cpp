#include "skpch.h"
#include "LayerStack.h"

namespace Skull
{
	LayerStack::LayerStack() 
	{
		
	}

	LayerStack::~LayerStack() // owned by the application
	{ 
		for (Layer* layer : m_Layers) 
		{
			delete layer;
		}
	}

	// IMPORTANT: daca dai POP, NU se sterg layerele, doar destructorul le sterge, 
	// poti sai dai PUSH inapoi daca ai nevoie de el
	// ALSO: Layerul trebuie sa fie primul renderat si Overlayul trebuie sa fie ultimul renderat
	void LayerStack::PushLayer(Layer* layer) // push la prima jumate din stack
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->OnAtach();
	}

	void LayerStack::PushOverlay(Layer* overlay) // push la a doua jumate din stack
	{ 
		m_Layers.emplace_back(overlay);
		overlay->OnAtach();
	}

	void LayerStack::PopLayer(Layer* layer) 
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		if (it != m_Layers.end()) 
		{
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay) 
	{
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end()) 
		{
			overlay->OnDetach();
			m_Layers.erase(it);
		}
	}
}