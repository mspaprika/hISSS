#include "Camera.h"
#include "CameraManager.h"



namespace HS
{
	HS_SINGLETON_IMPLEMENT(CameraManager)

	void CameraManager::PostInitialize()
	{
		m_pActiveCamera = new DebugCamera();

		m_vCameras.push_back(m_pActiveCamera);
	}

	void CameraManager::Update()
	{
		for (auto pCamera : m_vCameras)
		{
			pCamera->Update();
		}
	}
}