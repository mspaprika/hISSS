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

		bool OnUpdate() override;
		void OnRender(HS::RenderContext& rCtx) override;
		void OnInitialize() override;
		void OnShutdown() override;
		
	};
}