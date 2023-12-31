#pragma once


#ifdef HZ_PLATFORM_WINDOWS
	#if HZ_DYNAMIC_LINK
			#ifdef HZ_BUILD_DLL
				#define HAZEL_API __declspec(dllexport)
			#else
				#define HAZEL_API __declspec(dllimport)
			#endif
	#else 
		#define HAZEL_API
	#endif
#else
	#error Hazel only supports Windows!
#endif

#ifdef HZ_DEBUG
	#define HZ_ENABLE_ASSERTS
#endif

// "ASSERT" checks if the input is true (if it works out), and then it will output its __VA_ARGS__
#ifdef HZ_ENABLE_ASSERTS
	#define HZ_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HZ_ASSERT(x, ...) // These are used when in Dist and Release build, as they get stripped and does nothing. 
	#define HZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
