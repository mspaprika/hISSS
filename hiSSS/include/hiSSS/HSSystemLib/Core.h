#pragma once
//#include "../hiSSS/ext/Play3D/Play3d.h"
#include "../../../ext/Play3D/Play3d.h"

//#ifdef HS_PLATFORM_WINDOWS
//	#ifdef HS_BUILD_DLL
//		#define HS_API __declspec(dllexport)
//	#else 
//		#define HS_API __declspec(dllimport)
//	#endif
//#else 
//	#error Hisss!
//#endif


#define HS_SINGLETON_INTERFACE(className) \
public: \
	static className& Instance() { return *ms_pInstance; } \
	static void Initialize() { if (!ms_pInstance) { ms_pInstance = new className; }} \
	static void Destroy() { delete ms_pInstance; ms_pInstance = nullptr; } \
private: \
	static className* ms_pInstance; \

#define HS_SINGLETON_IMPLEMENT(className) className* className::ms_pInstance = nullptr;


#define HS_ASSERT(condition) \
		PLAY_ASSERT(condition) \

#define HS_ASSERT_MSG(condition, fmt, ...) \
		PLAY_ASSERT_MSG(condition, fmt, ...) \