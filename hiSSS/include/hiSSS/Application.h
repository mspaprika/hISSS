#pragma once
#include "HSSystemLib/Core.h"
#include "HSGraphicsLib/RenderContext.h"



namespace HS
{
	class /*HS_API*/ Application
	{

	public:
		Application();
		virtual ~Application();

		virtual bool OnUpdate() = 0;
		virtual void OnRender(RenderContext& rCtx) = 0;
		virtual void OnInitialize() = 0;
		virtual void OnShutdown() = 0;

		void Init();
		bool Update();
		void Render();

		void Run();
		void Shutdown();
	};

	// to be defined in CLIENT
	Application* CreateApplication();
}

