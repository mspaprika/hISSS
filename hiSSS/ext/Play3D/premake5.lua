-------------------------------------------------------------
-- Name: PlayBufferDx
-- Description: Play Buffer Framework
-------------------------------------------------------------
project "Play3D"
	kind "StaticLib"

	architecture "x64"

	--pchsource ("../PlayBufferDx/PlayBufferPCH.cpp")
	--pchheader ("PlayBufferPCH.h")

	nth.AddFiles()
	filter {}

	--Add Shader Files
	files {
		"**.hlsl",
		"**.hlsli"
	}

	--Vertex Shaders
	filter { "files:**VS.hlsl" }
	shadertype "Vertex"
	shadermodel ("5.0")
	shaderentry "VSMain"
	shadervariablename ("g_sh_%%(Filename)")
	shaderheaderfileoutput ("PlayShader%%(Filename).h")
	filter {}

	--Pixel Shaders
	filter { "files:**PS.hlsl" } 
	shadertype "Pixel"
	shadermodel ("5.0")
	shaderentry "PSMain"
	shadervariablename ("g_sh_%%(Filename)")
	shaderheaderfileoutput ("PlayShader%%(Filename).h")
	filter {}

	debugdir "."