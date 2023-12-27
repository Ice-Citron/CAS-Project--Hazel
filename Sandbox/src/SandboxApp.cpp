#include <Hazel.h>


class ExampleLayer : public Hazel::Layer {

public: 

	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override {}

	void OnEvent(Hazel::Event& event) override {
		
		if (event.GetEventType() == Hazel::EventType::KeyPressed) {
			Hazel::KeyPressedEvent& e = (Hazel::KeyPressedEvent&)event;
			if (e.GetKeyCode() == HZ_KEY_TAB)
				HZ_TRACE("Tab key is pressed!");
			HZ_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Hazel::Application {

public:

	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Hazel::ImGuiLayer());
	}

	~Sandbox() {}
};


Hazel::Application* Hazel::CreateApplication() {

	// In C++, when a subclass is instantiated, the constructor if the superclass is also called before the constructor of the subclass
	// 
	return new Sandbox();
}

