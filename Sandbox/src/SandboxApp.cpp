#include <Skull.h>

class ExampleLayer : public Skull::Layer{
public:
	ExampleLayer() : Layer("Example") {
		// nimic
	}

	void OnUpdate() override{
		SK_INFO("ExampleLayer::Update");
	}

	void OnEvent(Skull::Event& event) override {
		// SK_TRACE("{0}", event); // ERROR: probabil se sterge aiurea, are o problema dupa ToString()
	}
};

class Sandbox : public Skull::Application {

public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Skull::ImGuiLayer());
	}

	~Sandbox() {
		// nimic
	}

};

Skull::Application* Skull::CreateApplication() {
	return new Sandbox();
}