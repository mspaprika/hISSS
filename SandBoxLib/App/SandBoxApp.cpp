#include "hiSSS/HSAssetLib/AssetManager.h"
#include "hiSSS/HSGraphicsLib/Renderer.h"


#include "SandBoxApp.h"



namespace SB
{
	Sandbox::Sandbox()
	{

	}

	Sandbox::~Sandbox()
	{

	}

	bool Sandbox::OnUpdate(float dT)
	{ 




		return false; 
	}

	void Sandbox::OnRender()
	{

	}

	void Sandbox::OnInitialize()
	{
		HS::AssetManager::Instance().PostInitialize();
		HS::Renderer::Instance().PostInitialize();
	}

	void Sandbox::OnShutdown()
	{

	}
}



HS::Application* HS::CreateApplication()
{
	return new SB::Sandbox();
}