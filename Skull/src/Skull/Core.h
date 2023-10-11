#pragma once

#ifdef SK_PLATFORM_WINDOWS
	#ifdef SK_BUILD_DLL
		#define SKULL_API __declspec(dllexport)
	#else
		#define SKULL_API __declspec(dllimport)
	#endif // SK_BUILD_DLL
#else
	#error Numai pe windows merge!
#endif // SK_PLATFORM_WINDOWS

#ifdef HZ_DEBUG
	#define HZ_ENABLE_ASSERTS
#endif	

#ifdef SK_ENABLE_ASSERTS // scop? verifica o conditie daca nu a avut loc si va pune un breakpoint in cod si ne duce exact unde este problema
	#define SK_ASSERT(x, ...) { if(!(x)) { SK_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define SK_CORE_ASSERT(x, ...) { if(!(x)) { SK_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } } 
#else
	#define SK_ASSERT(x, ...)
	#define SK_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define SK_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1) // pentru ca sa incapa in ecran :D