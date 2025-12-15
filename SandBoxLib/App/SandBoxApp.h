#pragma once

#include <hiSSS.h>


namespace SB
{
	class Sandbox : public HS::Application
	{
	public:
		Sandbox();
	
		~Sandbox();

		bool OnUpdate() override;
		void OnRender() override;
		void OnInitialize() override;
		void OnShutdown() override;
		
	};
}