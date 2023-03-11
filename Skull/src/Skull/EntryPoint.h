#pragma once

#ifdef SK_PLATFORM_WINDOWS

extern Skull::Application* Skull::CreateApplication();

int main(int argc, char** argv) {
	
	Skull::Log::Init();
	SK_CORE_INFO("ceva");
	SK_WARN("altceva");

	auto app = Skull::CreateApplication();
	app->Run();
	delete app;
}

#endif // SK_PLATFORM_WINDOWS
