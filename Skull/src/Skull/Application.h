#pragma once

#include "Core.h";

namespace Skull {

	class SKULL_API Application{

	public:
		Application();
		virtual ~Application(); // punem virtual pt momentul cand punem in Sandbox ce-i aici

		void Run();
	};

	// to be defined in CLIENT
	Application* CreateApplication();
}

