#pragma once

#ifdef HS_PLATFORM_WINDOWS

extern HS::Application* HS::CreateApplication();

#define HS_ENTRY_POINT \
int PlayMain() \
{ \
	auto app = HS::CreateApplication(); \
	app->Run(); \
	app->Shutdown(); \
	delete app; \
	return 0; \
} \

#endif