

#include "HSSystemLib/CameraManager.h"
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
		CameraManager::Initialize();

		HS::AssetManager::Instance().PostInitialize();
		HS::Renderer::Instance().PostInitialize();
		HS::CameraManager::Instance().PostInitialize();

		OnInitialize();
	}

	void Application::Run()
	{
		Init();

		bool bQuit{ false };
		while (!bQuit)
		{
			if (System::BeginFrame() != RESULT_OK || Input::IsKeyPressed(VK_ESCAPE))
			{
				bQuit = true;
			}
			else
			{
				f32 dT = System::GetDeltaTime();
				bQuit = Update(dT);
				Render();
			}

			System::EndFrame();
		}
	}

	bool Application::Update(float dT)
	{
		HS::CameraManager::Instance().Update();

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

