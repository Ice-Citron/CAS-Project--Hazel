#pragma once


#ifdef HZ_PLATFORM_WINDOWS
	
extern Hazel::Application* Hazel::CreateApplication(); // extern marks that a variable of function exists externally to this source file. 
													   // This function is defined in SandboxApp.cpp

int main(int argc, char** argv) {

	//Initialising log.h on console
	Hazel::Log::Init();
	HZ_CORE_TRACE("Initialised Log!");	 //Hazel::Log::GetCoreLogger()->trace("Initialised Log!");
	int a = 5;
	HZ_INFO("Initialised Log!");    //Hazel::Log::GetClientLogger()->info("Initialised Log!");

	//Initialising the application
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif
