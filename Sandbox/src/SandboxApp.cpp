#include <Hazel.h>


class ExampleLayer : public Hazel::Layer {

public: 

	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override {
		HZ_INFO("ExampleLayer::Update");
	}

	void OnEvent(Hazel::Event& event) override {
		HZ_TRACE("{0}", event);
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

