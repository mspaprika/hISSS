#include "RenderContext.h"


namespace HS
{
	void RenderContext::Clear()
	{
		m_vUIRenderCommands.clear();
		m_vMeshRenderCommands.clear();
		m_vParticleRenderCommands.clear();
		m_vOverlayRenderCommands.clear();
		m_vPostFXRenderCommands.clear();
	}
}