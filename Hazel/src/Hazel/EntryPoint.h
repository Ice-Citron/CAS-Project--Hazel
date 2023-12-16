#pragma once


#ifdef HZ_PLATFORM_WINDOWS
	
extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv) {

	Hazel::Log::Init();
	HZ_CORE_TRACE("Initialised Log!");	 //Hazel::Log::GetCoreLogger()->trace("Initialised Log!");
	int a = 5;
	HZ_INFO("Initialised Log!");    //Hazel::Log::GetClientLogger()->info("Initialised Log!");

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif
