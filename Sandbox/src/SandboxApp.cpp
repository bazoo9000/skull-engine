#include <Skull.h>
#include "imgui/imgui.h"

class ExampleLayer : public Skull::Layer{
public:
	ExampleLayer() : Layer("Example") {
		// nimic
	}

	void OnUpdate() override{
		if (Skull::Input::IsKeyPressed(SK_KEY_TAB)) { // key polling
			SK_TRACE("Tab key pressed! (poll)");
		}
	}

	virtual void OnImGuiRender() {
		// fixed
		ImGui::Begin("Test");
		ImGui::Text("This is a text");
		ImGui::End();
	}

	void OnEvent(Skull::Event& event) override {
		if (event.GetEventType() == Skull::EventType::KeyPressed) { // key pressed event
			Skull::KeyPressedEvent& e = (Skull::KeyPressedEvent&)event;
			if (Skull::Input::IsKeyPressed(SK_KEY_TAB)) {
				SK_TRACE("Tab key pressed! (event)");
			}
			SK_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Skull::Application {

public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {
		// nimic
	}

};

Skull::Application* Skull::CreateApplication() {
	return new Sandbox();
}