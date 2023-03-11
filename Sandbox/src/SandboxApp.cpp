#include <Skull.h>

class Sandbox : public Skull::Application {

public:
	Sandbox() {
		// nimic
	}

	~Sandbox() {
		// nimic
	}

};

Skull::Application* Skull::CreateApplication() {
	return new Sandbox();
}