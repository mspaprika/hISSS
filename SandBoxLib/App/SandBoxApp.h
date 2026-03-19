#pragma once
#include <hiSSS.h>

#include "../HSGraphicsLib/RenderContext.h"


namespace SB
{
	class Sandbox : public HS::Application
	{
	public:
		Sandbox();
	
		~Sandbox();

		bool OnUpdate(float dT) override;
		void OnRender() override;
		void OnInitialize() override;
		void OnShutdown() override;
		
	};
}