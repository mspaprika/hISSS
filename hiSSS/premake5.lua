-------------------------------------------------------------
-- Name: GameMakerLib
-- Description: GameMaker emulator library
-------------------------------------------------------------
project "hiSSS"
	kind "StaticLib"
	language "C++"
 	
	architecture "x64"

	nth.AddFiles()

    --Add Shader Files
	files {
		"**.hlsl",
		"**.hlsli"
	}

	-- includedirs {}	

	-- libdirs { }

	local workspace_root = path.getabsolute("..")
    includedirs {
        path.join(workspace_root, "hiSSS/include/hiSSS/HSHeaderLib"),
        path.join(workspace_root, "hiSSS/include/hiSSS/HSSystemLib"),
        path.join(workspace_root, "hiSSS/include/ext/Play3D")
    }

	-- links { "Play3D", "HSHeaderLib", "HSSystemLib" }

	filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "HS_PLATFORM_WINDOWS"
            -- other macros
        }


  

	--Vertex Shaders
	filter { "files:**VS.hlsl" }
	shadertype "Vertex"
	shadermodel ("5.0")
	shaderentry "VSMain"
	shadervariablename ("g_sh_%%(Filename)")
	shaderheaderfileoutput ("../hiSSS/include/hiSSS/HSGraphicsLib/GeneratedShaders/PlayShader%%(Filename).h")
	filter {}

	--Pixel Shaders
	filter { "files:**PS.hlsl" } 
	shadertype "Pixel"
	shadermodel ("5.0")
	shaderentry "PSMain"
	shadervariablename ("g_sh_%%(Filename)")
	shaderheaderfileoutput ("../hiSSS/include/hiSSS/HSGraphicsLib/GeneratedShaders/PlayShader%%(Filename).h")
	filter {}
		
	debugdir "."

group("hiSSS Libs")
include("include/hiSSS/HSGraphicsLib/premake5.lua")
include("include/hiSSS/HSHeaderLib/premake5.lua")
include("include/hiSSS/HSSystemLib/premake5.lua")
include("ext/Play3D/premake5.lua")

