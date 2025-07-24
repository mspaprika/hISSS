///////////////////////////////////////////////////////////////////////////
//	Copyright (C) Sumo Digital Ltd. All rights reserved.
///////////////////////////////////////////////////////////////////////////

// We have to define this in one .cpp only to bring in our implementation code.
// It must be defined just before the #include "Play3d.h"
#define PLAY_IMPLEMENTATION
#include "../HissCoreLib/Play3D/Play3d.h"

// Play3d uses namespaces for each area of code.
// The top level namespace is Play3d
using namespace Play3d;


struct ShadowConstantData
{
	Matrix4x4f lightMatrix;
};

struct MyCustomData
{
	float a;
	float b;
	float c;
	float d;
};

int PlayMain()
{
	System::Initialise({ "GRP-TableChairsScene Example", 1920, 1080 });

	UI::FontId fontId = UI::GetDebugFont();

	Graphics::SamplerId linearSamplerId = Graphics::CreateLinearSampler();
	Graphics::MeshId sphereMesh = Graphics::CreateSphere(0.25, 32, 16, Colour::White);
	Graphics::MeshId planeMesh = Graphics::CreatePlane(2, 2, Colour::White);

	Graphics::MeshId cubeMesh = Graphics::CreateMeshCube(0.25f, Colour::Blueviolet);
	Graphics::MeshId chairMesh = Graphics::CreateMeshFromObjFile("Data/Chair.obj");
	Graphics::MeshId tableMesh = Graphics::CreateMeshFromObjFile("Data/WoodenTable.obj");
	Graphics::MeshId floorMesh = Graphics::CreateMeshFromObjFile("Data/BaseFloor.obj");
	Graphics::MeshId bowlMesh = Graphics::CreateMeshFromObjFile("Data/WoodenBowl.obj");
	Graphics::MeshId appleMesh = Graphics::CreateMeshFromObjFile("Data/Apple.obj");
	Graphics::MeshId wireStandMesh = Graphics::CreateMeshFromObjFile("Data/WireStand.obj");
	Graphics::MeshId stoolMesh = Graphics::CreateMeshFromObjFile("Data/WoodenStool.obj");

	Graphics::TextureId bowlTexture = Graphics::CreateTextureFromFile("Data/woodenbowl_diff.png");
	Graphics::TextureId stoolTexture = Graphics::CreateTextureFromFile("Data/woodenstool_diff.png");
	Graphics::TextureId tableTexture = Graphics::CreateTextureFromFile("Data/woodentable_diff.png");
	Graphics::TextureId floorTexture = Graphics::CreateTextureFromFile("Data/basefloor_diff.png");
	Graphics::TextureId appleTexture = Graphics::CreateTextureFromFile("Data/apple_diff.png");
	Graphics::TextureId chairTexture = Graphics::CreateTextureFromFile("Data/chair_diff.png");

	// Define a sampler for reading the shadow map.
	Graphics::SamplerId shadowSampler;
	{
		Graphics::SamplerDesc desc;
		desc.m_filter = Graphics::FilterMode::BILINEAR;
		desc.SetUniformAddressMode(Graphics::AddressMode::CLAMP);
		shadowSampler = Resources::CreateAsset<Graphics::Sampler>(desc);
	}

	// Define Shadow Casting material
	Graphics::MaterialId shadowCastMaterial;
	{
		Graphics::ComplexMaterialDesc desc;
		desc.SetupFromHLSLFile("ShadowCast", "Data/ShadowCastShader.hlsl");
		desc.m_state.m_cullMode = Graphics::CullMode::FRONT;
		desc.m_state.m_fillMode = Graphics::FillMode::SOLID;
		shadowCastMaterial = Resources::CreateAsset<Graphics::Material>(desc);
	}

	// Setup a global constant buffer to pass shadow matrices to our shaders
	ShadowConstantData shadowConstantData = {};
	Graphics::BufferId shadowConstantBufferId;
	{
		Graphics::BufferDesc desc;
		desc.SetConstantBuffer<ShadowConstantData>(&shadowConstantData);
		shadowConstantBufferId = Resources::CreateAsset<Graphics::Buffer>(desc);
	}

	// Define Fire Stone Idol material
	Graphics::MaterialId floorMaterial;
	{
		Graphics::ComplexMaterialDesc desc;
		desc.SetupFromHLSLFile("floorMaterial", "Data/ShadowReceiveShader.hlsl");
		desc.m_texture[0] = floorTexture;
		desc.m_sampler[0] = linearSamplerId;
		floorMaterial = Resources::CreateAsset<Graphics::Material>(desc);
	}

	Graphics::MaterialId chairMaterial;
	{
		Graphics::ComplexMaterialDesc desc;
		desc.SetupFromHLSLFile("chairMaterial", "Data/ShadowReceiveShader.hlsl");
		desc.m_texture[0] = chairTexture;
		desc.m_sampler[0] = linearSamplerId;
		chairMaterial = Resources::CreateAsset<Graphics::Material>(desc);
	}

	Graphics::MaterialId appleMaterial;
	{
		Graphics::ComplexMaterialDesc desc;
		desc.SetupFromHLSLFile("appleMaterial", "Data/ShadowReceiveShader.hlsl");
		desc.m_texture[0] = appleTexture;
		desc.m_sampler[0] = linearSamplerId;
		appleMaterial = Resources::CreateAsset<Graphics::Material>(desc);
	}

	Graphics::MaterialId stoolMaterial;
	{
		Graphics::ComplexMaterialDesc desc;
		desc.SetupFromHLSLFile("stoolMaterial", "Data/ShadowReceiveShader.hlsl");
		desc.m_texture[0] = stoolTexture;
		desc.m_sampler[0] = linearSamplerId;
		stoolMaterial = Resources::CreateAsset<Graphics::Material>(desc);
	}

	Graphics::MaterialId bowlMaterial;
	{
		Graphics::ComplexMaterialDesc desc;
		desc.SetupFromHLSLFile("bowlMaterial", "Data/ShadowReceiveShader.hlsl");
		desc.m_texture[0] = bowlTexture;
		desc.m_sampler[0] = linearSamplerId;
		bowlMaterial = Resources::CreateAsset<Graphics::Material>(desc);
	}

	Graphics::MaterialId tableMaterial;
	{
		Graphics::ComplexMaterialDesc desc;
		desc.SetupFromHLSLFile("tableMaterial", "Data/ShadowReceiveShader.hlsl");
		desc.m_texture[0] = tableTexture;
		desc.m_sampler[0] = linearSamplerId;
		tableMaterial = Resources::CreateAsset<Graphics::Material>(desc);
	}

	Graphics::MaterialId magicShaderaterial;
	{
		Graphics::ComplexMaterialDesc desc;
		desc.SetupFromHLSLFile("MagicShader", "Data/MagicShader.hlsl");
		desc.m_state.m_cullMode = Graphics::CullMode::NONE;
		desc.m_state.m_fillMode = Graphics::FillMode::SOLID;
		magicShaderaterial = Resources::CreateAsset<Graphics::Material>(desc);
	}


	MyCustomData myCustomData = {};
	Graphics::BufferId myCustomConstantBufferId;
	{
		Graphics::BufferDesc desc;
		desc.SetConstantBuffer<MyCustomData>(&myCustomData);
		myCustomConstantBufferId = Resources::CreateAsset<Graphics::Buffer>(desc);
	}
	

	Graphics::SetLightColour(0, Colour::Lightgoldenrodyellow);

	
	Graphics::SetDefaultRenderTargetClearColour(Colour::Skyblue);

	//////////////////////////////////////
	// Lets enter the main game loop
	//////////////////////////////////////
	bool bKeepGoing = true;
	while (bKeepGoing)
	{
		// BeginFrame should be called first, it will return RESULT_QUIT if the user has quit via 'Close' icons.
		if (System::BeginFrame() != RESULT_OK) 
		{
			bKeepGoing = false;
		}

		// We want to quit on the next frame if the user presses ESC.
		if (Input::IsKeyPressed(VK_ESCAPE)) 
		{
			bKeepGoing = false;
		}

		// Update Things
		Demo::UpdateDebugCamera();

		f32 t = System::GetElapsedTime() * 0.05f;
		
		Matrix4x4f modelMatrix = MatrixTranslate<f32>(0, 0, 0) * MatrixRotationY<f32>(2) * MatrixScale<f32>(0.1f, 0.1f, 0.1f);
		Matrix4x4f sphereMatrix = MatrixTranslate<f32>(0.f, 1.0f, 0.f);

		Matrix4x4f floorMatrix = MatrixTranslate<f32>(0, 0, 0) * MatrixRotationY<f32>(2) * MatrixScale<f32>(1.0f, 1.0f, 1.0f);
		Matrix4x4f tableMatrix = MatrixTranslate<f32>(0, sin(t), 0) * MatrixRotationY<f32>(2) * MatrixScale<f32>(1.0f, 1.0f, 1.0f);

		Matrix4x4f chairMatrix1 = MatrixTranslate<f32>(-0.5f, 0, 0.7f) * MatrixRotationY<f32>(3.0f) * MatrixScale<f32>(1.0f, 1.0f, 1.0f);
		Matrix4x4f chairMatrix2 = MatrixTranslate<f32>(0.5f, 0, 0.5f) * MatrixRotationY<f32>(3.301f) * MatrixScale<f32>(1.0f, 1.0f, 1.0f);
		Matrix4x4f chairMatrix3 = MatrixTranslate<f32>(-0.5f, 0, -0.5f) * MatrixRotationY<f32>(0.0f) * MatrixScale<f32>(1.0f, 1.0f, 1.0f);
		Matrix4x4f chairMatrix4 = MatrixTranslate<f32>(0.5f, 0, -0.7f) * MatrixRotationY<f32>(-0.5f) * MatrixScale<f32>(1.0f, 1.0f, 1.0f);

		Matrix4x4f bowlMatrix = MatrixTranslate<f32>(-0.7f, 0.96f, 0.3f) * MatrixRotationY<f32>(2) * MatrixScale<f32>(1.0f, 1.0f, 1.0f);

		Matrix4x4f appleMatrix1 = MatrixTranslate<f32>(0, 0, 0) * MatrixRotationY<f32>(2) * MatrixScale<f32>(1.0f, 1.0f, 1.0f);
		Matrix4x4f appleMatrix2 = MatrixTranslate<f32>(-0.05f, 0, 0.07f) * MatrixRotationY<f32>(2) * MatrixScale<f32>(1.0f, 1.0f, 1.0f);
		Matrix4x4f appleMatrix3 = MatrixTranslate<f32>(-0.07f, 0, 0.02f) * MatrixRotationY<f32>(2) * MatrixScale<f32>(1.0f, 1.0f, 1.0f);

		Matrix4x4f cubeMatrix = MatrixTranslate<f32>( 0.f, 0.35f, -0.1f) * MatrixRotationZ<f32>(1.f) * MatrixRotationX<f32>(1.5f) * MatrixScale<f32>(1.0f, 1.0f, 1.0f);
		Matrix4x4f wireStandMatrix = MatrixTranslate<f32>(0, 0.96f, 0) * MatrixRotationY<f32>(2) * MatrixScale<f32>(1.0f, 1.0f, 1.0f);
		Matrix4x4f stoolMatrix = MatrixTranslate<f32>(1.5f, 0, 0) * MatrixRotationY<f32>(1.58f) * MatrixScale<f32>(1.0f, 1.0f, 1.0f);
		

		// --------------------------------- Shadow Pass ---------------------------------
		constexpr u32 kShadowMapDim = 2048;
		Graphics::SurfaceSize shadowMapSurfaceSize{ kShadowMapDim, kShadowMapDim };
		Graphics::TextureId shadowMapSurface = Graphics::GetTransientSurface(shadowMapSurfaceSize, Graphics::TextureFormat::DEPTH);

		Graphics::TextureId TEMP_REMOVE_SURFACE = Graphics::GetTransientSurface(shadowMapSurfaceSize, Graphics::TextureFormat::RGBA);

		Vector3f lightDirection = normalize(Vector3f(1,2,1));
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

		Graphics::SetViewport(Graphics::Viewport(shadowMapSurfaceSize)); // prob scissor too.
		Graphics::SetViewMatrix(lightViewMatrix);
		Graphics::SetProjectionMatrix(lightProjectMatrix);

		// Clear the shadow map and Render the Shadow Casting Objects	
		Graphics::ClearDepthTarget(shadowMapSurface);
		Graphics::SetRenderTargets(TEMP_REMOVE_SURFACE, shadowMapSurface);

		// Colour is not important to us for the shadow map.
		// We only want to render to the Depth buffer.

		Graphics::SetMaterial(shadowCastMaterial);

		//Graphics::DrawMesh(floorMesh, floorMatrix);
		Graphics::DrawMesh(tableMesh, tableMatrix);

		Graphics::DrawMesh(bowlMesh, tableMatrix * bowlMatrix);
		Graphics::DrawMesh(wireStandMesh, tableMatrix * wireStandMatrix);
		Graphics::DrawMesh(cubeMesh, tableMatrix * wireStandMatrix * cubeMatrix);

		Graphics::DrawMesh(appleMesh, tableMatrix * bowlMatrix * appleMatrix1);
		Graphics::DrawMesh(appleMesh, tableMatrix * bowlMatrix * appleMatrix2);
		Graphics::DrawMesh(appleMesh, tableMatrix * bowlMatrix * appleMatrix3);

		Graphics::DrawMesh(stoolMesh, tableMatrix * stoolMatrix);

		Graphics::DrawMesh(chairMesh, tableMatrix * chairMatrix1);
		Graphics::DrawMesh(chairMesh, tableMatrix * chairMatrix2);
		Graphics::DrawMesh(chairMesh, tableMatrix * chairMatrix3);
		Graphics::DrawMesh(chairMesh, tableMatrix * chairMatrix4);

		// --------------------------------- Main Render Pass ---------------------------------

		auto displaySurfaceSize = Graphics::GetDisplaySurfaceSize();
		Graphics::TextureId mainRenderSurface = Graphics::GetTransientSurface(displaySurfaceSize, Graphics::TextureFormat::RGBA);
		Graphics::TextureId mainDepthSurface = Graphics::GetTransientSurface(displaySurfaceSize, Graphics::TextureFormat::DEPTH);

		Graphics::SetRenderTargets(mainRenderSurface, mainDepthSurface);

		Graphics::ClearRenderTarget(mainRenderSurface, Colour::Skyblue);
		Graphics::ClearDepthTarget(mainDepthSurface);

		// We now want to render from the main camera viewpoint.
		// We setup the view project matrices as normal.
		Demo::SetDebugCameraMatrices();

		//Graphics::SetRenderTargetsToSwapChain(true);
		
		//Demo::SetDebugCameraMatrices();

		shadowConstantData.lightMatrix = lightProjectMatrix * lightViewMatrix;
		Graphics::UpdateBuffer(shadowConstantBufferId, &shadowConstantData, sizeof(ShadowConstantData));
		Graphics::BindGlobalTexture(Graphics::kGlobalTextureSlotStart, shadowMapSurface, shadowSampler, Graphics::ShaderStageFlag::PIXEL_STAGE);
		Graphics::BindGlobalBuffer(Graphics::kGlobalBufferSlotStart, shadowConstantBufferId, Graphics::ShaderStageFlag::VERTEX_STAGE);

		
		//Graphics::DrawMesh(sphereMesh, sphereMatrix);
		//Graphics::DrawMesh(planeMesh, MatrixIdentity<4, f32>());

		Graphics::SetMaterial(floorMaterial);
		Graphics::DrawMesh(floorMesh, floorMatrix);

		Graphics::SetMaterial(tableMaterial);
		Graphics::DrawMesh(wireStandMesh, tableMatrix * wireStandMatrix);
		Graphics::DrawMesh(tableMesh, tableMatrix);

		Graphics::SetMaterial(bowlMaterial);
		Graphics::DrawMesh(bowlMesh, tableMatrix * bowlMatrix);


		Graphics::SetMaterial(appleMaterial);
		Graphics::DrawMesh(appleMesh, tableMatrix * bowlMatrix * appleMatrix1);
		Graphics::DrawMesh(appleMesh, tableMatrix * bowlMatrix * appleMatrix2);
		Graphics::DrawMesh(appleMesh, tableMatrix * bowlMatrix* appleMatrix3);

		Graphics::SetMaterial(stoolMaterial);
		Graphics::DrawMesh(stoolMesh, tableMatrix * stoolMatrix);

		Graphics::SetMaterial(chairMaterial);
		Graphics::DrawMesh(chairMesh, tableMatrix * chairMatrix1);
		Graphics::DrawMesh(chairMesh, tableMatrix * chairMatrix2);
		Graphics::DrawMesh(chairMesh, tableMatrix * chairMatrix3);
		Graphics::DrawMesh(chairMesh, tableMatrix * chairMatrix4);
		
		Graphics::DrawMesh(cubeMesh, tableMatrix * wireStandMatrix * cubeMatrix);

		// UI Debug Text
		UI::DrawString(fontId, Vector2f(20, 20), Colour::White, "Table Chairs Scene");
		Graphics::BeginPrimitiveBatch();
		Graphics::DrawLine(lightDirection * 2.f, Vector3f(0,0,0), Colour::Yellow);
		Graphics::EndPrimitiveBatch();

		// --------------------------------- PostFX Pass ---------------------------------
		Graphics::SetRenderTargetsToSwapChain(false);

		Graphics::BindGlobalTexture(Graphics::kGlobalTextureSlotStart, mainRenderSurface, linearSamplerId, Graphics::ShaderStageFlag::PIXEL_STAGE);
		Graphics::BindGlobalBuffer(Graphics::kGlobalBufferSlotStart, myCustomConstantBufferId, Graphics::ShaderStageFlag::PIXEL_STAGE);

		Graphics::SetMaterial(magicShaderaterial);
		Graphics::DrawWithoutVertices(3);

		Graphics::BindGlobalTexture(Graphics::kGlobalTextureSlotStart, Graphics::TextureId(), Graphics::SamplerId(), Graphics::ShaderStageFlag::PIXEL_STAGE);


		// Finally we signal the framework to finish the frame.
		System::EndFrame();
	}

	// Make sure to shutdown the library before we end our main function.
	System::Shutdown();

	return 0;
};
