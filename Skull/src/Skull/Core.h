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

#define BIT(x) (1 << x)