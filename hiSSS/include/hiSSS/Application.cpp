
#include "Application.h"

namespace HS
{
	
	Application::Application()
	{

	}

		
	Application::~Application()
	{

	}

	void Application::Init()
	{
		OnInitialize();
	}

	void Application::Run()
	{
		Init();

		bool bQuit{ false };
		while (!bQuit)
		{
			bQuit = Update();
			Render();
		}
	}

	bool Application::Update()
	{
		return OnUpdate();
	}

	void Application::Render()
	{
		OnRender();
	}
	
	void Application::Shutdown()
	{
		OnShutdown();
	}

}

