

#include "HSGraphicsLib/Renderer.h"
#include "HSAssetLib/AssetManager.h"
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
		System::Initialise({ "hiSSS Engine", 1920, 1080 });

		Renderer::Initialize();
		AssetManager::Initialize();

		OnInitialize();
	}

	void Application::Run()
	{
		Init();

		/*int x = 0;

		HS_ASSERT(x > 0)*/

		bool bQuit{ false };
		while (!bQuit)
		{
			bQuit = Update();
			Render();

			System::EndFrame();
		}
	}

	bool Application::Update()
	{
		return OnUpdate();
	}

	void Application::Render()
	{
		auto& ctx = Renderer::Instance().GetRenderContext();
		OnRender(ctx);

		Renderer::Instance().Render();
	}
	
	void Application::Shutdown()
	{
		OnShutdown();
		System::Shutdown();
	}

}

