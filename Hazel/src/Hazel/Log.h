#pragma once

#include "Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"


namespace Hazel {

	class HAZEL_API Log {

	public:

		Log();
		~Log();

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:

		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}


//Defining Core Log Macros
#define HZ_CORE_TRACE(...)      ::Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_DEBUGS(...)     ::Hazel::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define HZ_CORE_INFO(...)       ::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...)       ::Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...)      ::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HZ_CORE_CRITICAL(...)   ::Hazel::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Defining Client Log Macros
#define HZ_TRACE(...)     ::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HZ_DEBUGS(...)    ::Hazel::Log::GetClientLogger()->debug(__VA_ARGS__) // need to change name from HZ_DEBUG because of naming collision with premake5.lua
#define HZ_INFO(...)      ::Hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define HZ_WARN(...)      ::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HZ_ERROR(...)     ::Hazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define HZ_CRITICAL(...)  ::Hazel::Log::GetClientLogger()->critical(__VA_ARGS__)




