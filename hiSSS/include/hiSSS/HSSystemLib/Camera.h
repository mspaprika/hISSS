#pragma once
//#include "../hiSSS/ext/Play3D/Play3d.h"
#include "../../../ext/Play3D/Play3d.h"
#include <random>

namespace HS
{
	using namespace Play3d;

	class Camera
	{
	public:
		Camera() {}
		virtual ~Camera() {}

		// Update should be overloaded to update internal matrices.
		virtual void Update() = 0;

		const Matrix4x4f& GetView() const { return m_viewMatrix; }
		const Matrix4x4f& GetProject() const { return m_projMatrix; }


	protected:
		f32 m_fAzimuth = 0.f;
		f32 m_fElevation = kfPi / 16;
		f32 m_fNearClip = 0.1f;
		f32 m_fFarClip = 100.f;
		f32 m_fFOV = kfPi / 4.f;

		Matrix4x4f m_viewMatrix;
		Matrix4x4f m_projMatrix;
	};

	class DebugCamera : public Camera
	{
	public:
		DebugCamera();
		void Update() override;
		//void SetPosition(const Vector3f& fPosition, f32 fAzimuth, f32 fElevation);
		//oid SetFOV(f32 fFOV, f32 fNearClip, f32 fFarClip);

	private:
		Vector3f m_eyePosition = Vector3f(0.f, 1.f, -3.5f);
		Vector3f m_vForward = Vector3f(0, 0, 1);
		Vector3f m_vRight = Vector3f(1, 0, 0);
		Vector3f m_vUp = Vector3f(0, 1, 0);
		bool m_bIsCaptured = false;
	};

	class PlayerCamera : public Camera
	{
	public:
		PlayerCamera() {}
		void Update() override {}
		//void SetPlayer(Player* p);

	/*	void ApplyShakeEffect(float dT) {}
		void Shake(float intensity, float duration);
		bool IsActive() { return m_shakeActive; }*/

	private:
		//Player* m_pPlayer{ nullptr };
		float m_offset{ 5.0f };

		std::uniform_real_distribution< float > m_distribution;
		std::default_random_engine m_generator;
		float m_shakeDuration{ 0.0f };
		float m_shakeIntensity{ 0.0f };
		float m_shakeTimer{ 0.0f };
		bool m_shakeActive{ false };

	};

}