#pragma once
#include <Play3d.h>

using namespace Play3d;
namespace HS
{
	struct RenderCommand
	{
		Matrix4x4f worldMtx{ Play3d::MatrixIdentity4x4f() };
		Graphics::MaterialId materialId;
	};

	struct MeshRenderCommand : RenderCommand
	{
		Graphics::MeshId meshId;
		u32 submeshIdx{ 0 };
	};

	struct ParticleRenderCommand : RenderCommand
	{
		Graphics::BufferId particleBuffId;
		u32 particleCount;
		Graphics::MaterialId materialId;
	};

	struct PostFXRenderCommand
	{
		Graphics::ShaderId shaderId;
		Graphics::MaterialId materialId;
	};

	struct UIRenderCommand : RenderCommand
	{

	};

	struct OverlayRenderCommand : UIRenderCommand
	{

	};
}