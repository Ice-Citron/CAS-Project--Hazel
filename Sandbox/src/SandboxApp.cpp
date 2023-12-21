#include <Hazel.h>


class Sandbox : public Hazel::Application {

public:

	Sandbox() {}
	~Sandbox() {}
};


Hazel::Application* Hazel::CreateApplication() {

	// In C++, when a subclass is instantiated, the constructor if the superclass is also called before the constructor of the subclass
	// 
	return new Sandbox();
}

