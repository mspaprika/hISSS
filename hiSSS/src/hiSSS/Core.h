#pragma once

#ifdef HS_PLATFORM_WINDOWS
	#ifdef HS_BUILD_DLL
		#define HISSS_API __declspec(dllexport)
	#else 
		#define HISSS_API __declspec(dllimport)
	#endif
#else 
	#error Hisss!
#endif


#define HS_SINGLETON_INTERFACE(className) \
public: \
	static className& Instance() { return *ms_pInstance; } \
	static void Initialize() { if (!ms_pInstance) { ms_pInstance = new className; }} \
	static void Destroy() { delete ms_pInstance; ms_pInstance = nullptr; } \
private: \
	static className* ms_pInstance; \

#define HS_SINGLETON_IMPLEMENT(className) className* className::ms_pInstance = nullptr;