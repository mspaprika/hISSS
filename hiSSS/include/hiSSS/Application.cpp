

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
			if (System::BeginFrame() != RESULT_OK || Input::IsKeyPressed(VK_ESCAPE))
			{
				bQuit = true;
			}

			f32 dT = System::GetDeltaTime();
			bQuit = Update(dT);
			Render();

			System::EndFrame();
		}
	}

	bool Application::Update(float dT)
	{
		return OnUpdate(dT);
	}

	void Application::Render()
	{
		auto& ctx = Renderer::Instance().GetRenderContext();
		OnRender();

		Renderer::Instance().Render();
	}
	
	void Application::Shutdown()
	{
		OnShutdown();
		System::Shutdown();
	}

}

