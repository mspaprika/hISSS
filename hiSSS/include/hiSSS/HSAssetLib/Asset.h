#pragma once
#include <hiSSS.h>


namespace HS
{
	enum class AssetType : int8_t
	{
		INVALID_TYPE = -1,
		FLOOR,
		TABLE,
		CHAIR,
		APPLE,
		BOWL,
		STOOL,
	};

	class Asset
	{
	public:

		Asset(const Graphics::MaterialId& rMaterial) : m_material(rMaterial) {}
		~Asset() {}

		Graphics::MaterialId GetMaterial() { return m_material; }

	private:
		Graphics::MaterialId m_material{};
	};


	class Model : public Asset
	{
	public:

		Model(const Graphics::MaterialId& rMaterial, const Graphics::MeshId& rMesh) : Asset(rMaterial), m_mesh(rMesh) {}
		~Model() {}

		Graphics::MeshId GetMesh() { return m_mesh; }

	private:

		Graphics::MeshId m_mesh{};
	};
}