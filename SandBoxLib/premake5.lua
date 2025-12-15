-------------------------------------------------------------
-- Name: RecognEyesLib
-- Description: Library that contains most of the game code
-------------------------------------------------------------
project "SandBoxLib"
	kind "StaticLib"
	architecture "x64"
		
	-- files {
	-- 	"premake5.lua",
	-- 	"**.cpp",
	-- 	"**.h",
	-- 	"**.natvis"
	-- }
	
	nth.AddFiles()

	--Add Shader Files
	files {
		"**.hlsl",
		"**.hlsli"
	}
	
	filter "system:windows"
	cppdialect "C++20"
	staticruntime "On"
	systemversion "latest"
	
	defines
	{
		"HS_PLATFORM_WINDOWS", 
		-- macros
	}
	
	filter {}
	
	local workspace_root = path.getabsolute("..")
    includedirs {
        path.join(workspace_root, "hiSSS/include/hiSSS/HSHeaderLib"),
        path.join(workspace_root, "hiSSS/include/hiSSS/HSSystemLib"),
        path.join(workspace_root, "hiSSS/include/ext/Play3D")
    }

	filter {}
	links 
	{
		"Play3D",
		"hiSSS", "HSHeaderLib", "HSSystemLib"
	}

		--Vertex Shaders
	filter { "files:**VS.hlsl" }
	shadertype "Vertex"
	shadermodel ("5.0")
	shaderentry "VSMain"
	shadervariablename ("g_sh_%%(Filename)")
	shaderheaderfileoutput ("../SandBoxLib/src/GeneratedShaders/PlayShader%%(Filename).h")
	filter {}

	--Pixel Shaders
	filter { "files:**PS.hlsl" } 
	shadertype "Pixel"
	shadermodel ("5.0")
	shaderentry "PSMain"
	shadervariablename ("g_sh_%%(Filename)")
	shaderheaderfileoutput ("../SandBoxLib/src/GeneratedShaders/PlayShader%%(Filename).h")
	
	

	debugdir "."