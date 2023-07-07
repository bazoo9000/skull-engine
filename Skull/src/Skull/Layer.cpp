#include "skpch.h"
#include "Layer.h"

namespace Skull {

	Layer::Layer(const std::string& debugName)
		: m_DebugName(debugName){
		// nimic, doar ii dam numele
	}

	Layer::~Layer() {
		// nimic
	}
}