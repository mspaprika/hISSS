#include "SandBoxApp.h"



namespace SB
{
	Sandbox::Sandbox()
	{

	}

	Sandbox::~Sandbox()
	{

	}

	bool Sandbox::OnUpdate()
	{ 




		return false; 
	}

	void Sandbox::OnRender()
	{

	}

	void Sandbox::OnInitialize()
	{

	}

	void Sandbox::OnShutdown()
	{

	}
}



HS::Application* HS::CreateApplication()
{
	return new SB::Sandbox();
}