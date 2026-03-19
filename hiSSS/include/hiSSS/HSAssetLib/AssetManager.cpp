#include "AssetManager.h"


namespace HS
{
	HS_SINGLETON_IMPLEMENT(AssetManager)

	void AssetManager::CreateMaterialAsset(const MaterialAssetDesc& rDesc)
	{
		HS_ASSERT(rDesc.type != AssetType::INVALID_TYPE)

		m_assets[ rDesc.type ] = new Asset(rDesc.material);
	}

	void AssetManager::CreateModelAsset(const ModelAssetDesc& rDesc)
	{
		HS_ASSERT(rDesc.type != AssetType::INVALID_TYPE)

		m_assets[ rDesc.type ] = new Model(rDesc.material, rDesc.mesh);
	}

	void AssetManager::PostInitialize()
	{
		InitializeInternalAssets();
	}

	void AssetManager::InitializeInternalAssets()
	{
		//UI::FontId fontId = UI::GetDebugFont();
		
			Graphics::SamplerId linearSamplerId = Graphics::CreateLinearSampler();

			/*Graphics::MeshId sphereMesh = Graphics::CreateSphere(0.25, 32, 16, Colour::White);
			Graphics::MaterialId magicShaderaterial;
			{
				Graphics::ComplexMaterialDesc desc;
				desc.SetupFromHLSLFile("MagicShader", "Data/MagicShader.hlsl");
				desc.m_state.m_cullMode = Graphics::CullMode::NONE;
				desc.m_state.m_fillMode = Graphics::FillMode::SOLID;
				magicShaderaterial = Resources::CreateAsset<Graphics::Material>(desc);
			}*/
			/*Graphics::TextureId sphereTexture = Graphics::CreateTextureFromFile("Data/apple_diff.png");

			Graphics::MeshId cubeMesh = Graphics::CreateMeshCube(0.25f, Colour::Blueviolet);
			Graphics::MeshId planeMesh = Graphics::CreatePlane(2, 2, Colour::White);*/
		
			//Graphics::MeshId floorMesh = Graphics::CreateMeshFromObjFile("Data/BaseFloor.obj");
			Graphics::MeshId planeMesh = Graphics::CreatePlane(2, 2, Colour::White);
			Graphics::TextureId floorTexture = Graphics::CreateTextureFromFile("Data/basefloor_diff.png");
			Graphics::MaterialId floorMaterial;
			{
				Graphics::ComplexMaterialDesc desc;
				desc.SetupFromHLSLFile("floorMaterial", "../SourceAssets/Shaders/TerrainShader.hlsl");
				desc.m_texture[0] = floorTexture;
				desc.m_sampler[0] = linearSamplerId;
				floorMaterial = Resources::CreateAsset<Graphics::Material>(desc);
			}

			m_assets[ AssetType::FLOOR ] = new Model({ floorMaterial, planeMesh });


			Graphics::MeshId tableMesh = Graphics::CreateMeshFromObjFile("Data/WoodenTable.obj");
			Graphics::TextureId tableTexture = Graphics::CreateTextureFromFile("Data/woodentable_diff.png");
			Graphics::MaterialId tableMaterial;
			{
				Graphics::ComplexMaterialDesc desc;
				desc.SetupFromHLSLFile("tableMaterial", "../SourceAssets/Shaders/TerrainShader.hlsl");
				desc.m_texture[0] = tableTexture;
				desc.m_sampler[0] = linearSamplerId;
				tableMaterial = Resources::CreateAsset<Graphics::Material>(desc);
			}

			m_assets[ AssetType::TABLE ] = new Model({ tableMaterial, tableMesh });

			//Graphics::MeshId chairMesh = Graphics::CreateMeshFromObjFile("Data/Chair.obj");
			//Graphics::TextureId chairTexture = Graphics::CreateTextureFromFile("Data/chair_diff.png");
			//Graphics::MaterialId chairMaterial;
			//{
			//	Graphics::ComplexMaterialDesc desc;
			//	desc.SetupFromHLSLFile("chairMaterial", "Data/ShadowReceiveShader.hlsl");
			//	desc.m_texture[0] = chairTexture;
			//	desc.m_sampler[0] = linearSamplerId;
			//	chairMaterial = Resources::CreateAsset<Graphics::Material>(desc);
			//}

			//m_assets[ AssetType::CHAIR ] = new Model({ chairMaterial, chairMesh });

			//Graphics::MeshId appleMesh = Graphics::CreateMeshFromObjFile("Data/Apple.obj");
			//Graphics::TextureId appleTexture = Graphics::CreateTextureFromFile("Data/apple_diff.png");
			//Graphics::MaterialId appleMaterial;
			//{
			//	Graphics::ComplexMaterialDesc desc;
			//	desc.SetupFromHLSLFile("appleMaterial", "Data/ShadowReceiveShader.hlsl");
			//	desc.m_texture[0] = appleTexture;
			//	desc.m_sampler[0] = linearSamplerId;
			//	appleMaterial = Resources::CreateAsset<Graphics::Material>(desc);
			//}

			//m_assets[ AssetType::APPLE ] = new Model({ appleMaterial, appleMesh });

			//Graphics::MeshId bowlMesh = Graphics::CreateMeshFromObjFile("Data/WoodenBowl.obj");
			//Graphics::TextureId bowlTexture = Graphics::CreateTextureFromFile("Data/woodenbowl_diff.png");
			//Graphics::MaterialId bowlMaterial;
			//{
			//	Graphics::ComplexMaterialDesc desc;
			//	desc.SetupFromHLSLFile("bowlMaterial", "Data/ShadowReceiveShader.hlsl");
			//	desc.m_texture[0] = bowlTexture;
			//	desc.m_sampler[0] = linearSamplerId;
			//	bowlMaterial = Resources::CreateAsset<Graphics::Material>(desc);
			//}

			//m_assets[ AssetType::BOWL ] = new Model({ bowlMaterial, bowlMesh });

			//Graphics::MeshId stoolMesh = Graphics::CreateMeshFromObjFile("Data/WoodenStool.obj");
			//Graphics::TextureId stoolTexture = Graphics::CreateTextureFromFile("Data/woodenstool_diff.png");
			//Graphics::MaterialId stoolMaterial;
			//{
			//	Graphics::ComplexMaterialDesc desc;
			//	desc.SetupFromHLSLFile("stoolMaterial", "Data/ShadowReceiveShader.hlsl");
			//	desc.m_texture[0] = stoolTexture;
			//	desc.m_sampler[0] = linearSamplerId;
			//	stoolMaterial = Resources::CreateAsset<Graphics::Material>(desc);
			//}

			//m_assets[ AssetType::STOOL ] = new Model({ stoolMaterial, stoolMesh });

			//Graphics::MeshId wireStandMesh = Graphics::CreateMeshFromObjFile("Data/WireStand.obj");
		
		
			// Define a sampler for reading the shadow map.
			//Graphics::SamplerId shadowSampler;
			//{
			//	Graphics::SamplerDesc desc;
			//	desc.m_filter = Graphics::FilterMode::BILINEAR;
			//	desc.SetUniformAddressMode(Graphics::AddressMode::CLAMP);
			//	shadowSampler = Resources::CreateAsset<Graphics::Sampler>(desc);
			//}
		
			//// Define Shadow Casting material
			//Graphics::MaterialId shadowCastMaterial;
			//{
			//	Graphics::ComplexMaterialDesc desc;
			//	desc.SetupFromHLSLFile("ShadowCast", "Data/ShadowCastShader.hlsl");
			//	desc.m_state.m_cullMode = Graphics::CullMode::FRONT;
			//	desc.m_state.m_fillMode = Graphics::FillMode::SOLID;
			//	shadowCastMaterial = Resources::CreateAsset<Graphics::Material>(desc);
			//}
		
			// Setup a global constant buffer to pass shadow matrices to our shaders
			/*ShadowConstantData shadowConstantData = {};
			Graphics::BufferId shadowConstantBufferId;
			{
				Graphics::BufferDesc desc;
				desc.SetConstantBuffer<ShadowConstantData>(&shadowConstantData);
				shadowConstantBufferId = Resources::CreateAsset<Graphics::Buffer>(desc);
			}*/
		
			// Define Fire Stone Idol material
			
		
			
		
			
		
			
		
			
		
			
		
			
		
		
			/*MyCustomData myCustomData = {};
			Graphics::BufferId myCustomConstantBufferId;
			{
				Graphics::BufferDesc desc;
				desc.SetConstantBuffer<MyCustomData>(&myCustomData);
				myCustomConstantBufferId = Resources::CreateAsset<Graphics::Buffer>(desc);
			}*/
		
		
			Graphics::SetLightColour(0, Colour::Lightgoldenrodyellow);
		
		
			Graphics::SetDefaultRenderTargetClearColour(Colour::Skyblue);
	}

	Asset* AssetManager::GetAsset(AssetType type)
	{
		auto it = m_assets.find(type);
		if (it != m_assets.end())
		{
			return it->second;
		}

		return nullptr;
	}
}