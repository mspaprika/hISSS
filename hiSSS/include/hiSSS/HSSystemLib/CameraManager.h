#pragma once
#include "Core.h"


namespace HS
{
	class Camera;

	class CameraManager
	{
	public:
		HS_SINGLETON_INTERFACE(CameraManager)

	public:
		void PostInitialize();

		void Update();

		Camera* GetActiveCamera() { return m_pActiveCamera; }
	private:

		std::vector<Camera*> m_vCameras{};
		Camera* m_pActiveCamera{ nullptr };
	};
}


