#include "Renderer.h"
#include "RenderContext.h"
#include "hiSSS/HSAssetLib/AssetManager.h"

namespace HS
{
	HS_SINGLETON_IMPLEMENT(Renderer)


	void Renderer::PostInitialize()
	{
		InitializePipeline();
	}

	void Renderer::InitializePipeline()
	{
		m_linearSamplerId = Graphics::CreateLinearSampler();


		Graphics::SetLightColour(0, Colour::Lightgoldenrodyellow);
		Graphics::SetDefaultRenderTargetClearColour(Colour::Skyblue);

		{
			Graphics::BufferDesc desc;
			desc.SetConstantBuffer<ConstantBuffer>(&m_cData);
			m_cbufferId = Resources::CreateAsset<Graphics::Buffer>(desc);
		}


	}
	

	void Renderer::Render()
	{ 
		m_renderCtx.Clear();

		auto& rAM{ AssetManager::Instance() };
		Model* pTable = static_cast<Model*>(rAM.GetAsset(AssetType::TABLE));

		MeshRenderCommand cmd;
		cmd.materialId = pTable->GetMaterial();
		cmd.meshId = pTable->GetMesh();
		m_renderCtx.AddRenderCommand(cmd);

		Vector3f lightDirection = normalize(Vector3f(1, 2, 1));
		Graphics::SetLightDirection(0, lightDirection);
		Matrix4x4f lightViewMatrix = MatrixLookatRH(lightDirection, Vector3f(0, 0, 0), Vector3f(0, 1, 0));
		
		constexpr f32 kShadowBound = 2.f;
		f32 fClipLeft = -kShadowBound;
		f32 fClipRight = kShadowBound;
		f32 fClipTop = kShadowBound;
		f32 fClipBottom = -kShadowBound;
		f32 fClipNear = 0.1f;
		f32 fClipFar = 10.f;
		
		Matrix4x4f lightProjectMatrix = MatrixOrthoProjectRH(fClipLeft, fClipRight, fClipBottom, fClipTop, fClipNear, fClipFar);
		
		Graphics::SetViewport(Graphics::Viewport({ 2048 , 2048 })); // prob scissor too.
		Graphics::SetViewMatrix(lightViewMatrix);
		Graphics::SetProjectionMatrix(lightProjectMatrix);
		
		auto displaySurfaceSize = Graphics::GetDisplaySurfaceSize();
		Graphics::TextureId mainRenderSurface = Graphics::GetTransientSurface(displaySurfaceSize, Graphics::TextureFormat::RGBA);
		Graphics::TextureId mainDepthSurface = Graphics::GetTransientSurface(displaySurfaceSize, Graphics::TextureFormat::DEPTH);
		
		// Clear the shadow map and Render the Shadow Casting Objects	
		Graphics::ClearRenderTarget(mainRenderSurface, Colour::Skyblue);
		Graphics::ClearDepthTarget(mainRenderSurface);
		//Graphics::SetRenderTargets(TEMP_REMOVE_SURFACE, shadowMapSurface);

		Graphics::SetRenderTargetsToSwapChain(true);

		
		m_cData.lightMatrix = lightProjectMatrix * lightViewMatrix;
		Graphics::UpdateBuffer(m_cbufferId, &m_cData, sizeof(m_cData));
		Graphics::BindGlobalTexture(Graphics::kGlobalTextureSlotStart, mainRenderSurface, m_linearSamplerId, Graphics::ShaderStageFlag::PIXEL_STAGE);
		Graphics::BindGlobalBuffer(Graphics::kGlobalBufferSlotStart, m_cbufferId, Graphics::ShaderStageFlag::VERTEX_STAGE);


		Graphics::SetMaterial(cmd.materialId);
		Graphics::DrawMesh(cmd.meshId, cmd.worldMtx);

		Graphics::SetRenderTargetsToSwapChain(false);
		
		Graphics::BindGlobalTexture(Graphics::kGlobalTextureSlotStart, mainRenderSurface, m_linearSamplerId, Graphics::ShaderStageFlag::PIXEL_STAGE);
		Graphics::BindGlobalBuffer(Graphics::kGlobalBufferSlotStart, m_cbufferId, Graphics::ShaderStageFlag::PIXEL_STAGE);
		
		Graphics::BindGlobalTexture(Graphics::kGlobalTextureSlotStart, Graphics::TextureId(), Graphics::SamplerId(), Graphics::ShaderStageFlag::PIXEL_STAGE);
	}
}