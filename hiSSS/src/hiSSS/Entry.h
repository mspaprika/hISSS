#pragma once

#ifdef HS_PLATFORM_WINDOWS

extern Hisss::Application* Hisss::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Hisss::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif