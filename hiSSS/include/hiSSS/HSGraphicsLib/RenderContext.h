#pragma once
#include"RenderCommand.h"

namespace HS
{
	namespace RenderPass
	{
		enum Enum : uint32_t
		{
			SHADOW,
			SCENE,
			PARTICLE,
			UI,
			POST_FX,

			OVERLAY,
		};
	}


	class RenderContext
	{
	public: 

		inline void AddRenderCommand(const UIRenderCommand& command)
		{
			m_vUIRenderCommands.push_back(command);
		}

		inline void AddRenderCommand(const MeshRenderCommand& command)
		{
			m_vMeshRenderCommands.push_back(command);
		}

		inline void AddRenderCommand(const ParticleRenderCommand& command)
		{
			m_vParticleRenderCommands.push_back(command);
		}

		inline void AddRenderCommand(const OverlayRenderCommand& command)
		{
			m_vOverlayRenderCommands.push_back(command);
		}

		inline void AddRenderCommand(const PostFXRenderCommand& command)
		{
			m_vPostFXRenderCommands.push_back(command);
		}

		void Clear();

		const std::vector<UIRenderCommand>& GetUICommands() const { return m_vUIRenderCommands; }
		const std::vector<MeshRenderCommand>& GetMeshCommands() const { return m_vMeshRenderCommands; }

	private:
		std::vector<UIRenderCommand> m_vUIRenderCommands;
		std::vector<MeshRenderCommand> m_vMeshRenderCommands;
		std::vector<ParticleRenderCommand> m_vParticleRenderCommands;
		std::vector<OverlayRenderCommand> m_vOverlayRenderCommands;
		std::vector<PostFXRenderCommand> m_vPostFXRenderCommands;
	};
}