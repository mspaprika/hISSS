#pragma once
#include "Core.h"

namespace Hisss
{
	class HISSS_API Application
	{

	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// to be defined in CLIENT
	Application* CreateApplication();
}

