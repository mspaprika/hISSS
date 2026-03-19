#pragma once
#include <hiSSS.h>
#include "RenderContext.h"


namespace HS
{
	struct ConstantBuffer
	{
		Matrix4x4f lightMatrix;
	};
	
	class Renderer
	{
	public:
		HS_SINGLETON_INTERFACE(Renderer)

	public:
		void PostInitialize();

		void InitializePipeline();

		RenderContext& GetRenderContext() { return m_renderCtx; }
		void ClearRenderContext() {}


		void Render();

		//template <typename T>



	private:
		RenderContext m_renderCtx;

		Graphics::SamplerId m_linearSamplerId{};

		Graphics::BufferId m_cbufferId{};

		ConstantBuffer m_cData{};
	};
}