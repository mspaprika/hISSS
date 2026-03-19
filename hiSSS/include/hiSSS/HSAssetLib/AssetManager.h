#pragma once
#include <hiSSS.h>
#include "Asset.h"


namespace HS
{
	struct MaterialAssetDesc
	{
		Graphics::MaterialId material{};
		AssetType type{ AssetType::INVALID_TYPE };
	};

	struct ModelAssetDesc : MaterialAssetDesc
	{
		Graphics::MeshId mesh{};
	};

	class AssetManager
	{
	public:
		HS_SINGLETON_INTERFACE(AssetManager)

	public:

		void PostInitialize();

		void InitializeInternalAssets();

		void CreateMaterialAsset(const MaterialAssetDesc& rDesc);

		void CreateModelAsset(const ModelAssetDesc& rDesc);

		Asset* GetAsset(AssetType type);

	private:
		std::unordered_map<AssetType, Asset*> m_assets{};
	};
}