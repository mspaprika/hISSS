-------------------------------------------------------------
-- Name: GameMakerLib
-- Description: GameMaker emulator library
-------------------------------------------------------------
project "hiSSS"
	kind "StaticLib"
	language "C++"
 	
	architecture "x64"

	nth.AddFiles()

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
		
	debugdir "."

group("hiSSS Libs")
include("include/hiSSS/HSHeaderLib/premake5.lua")
include("include/hiSSS/HSSystemLib/premake5.lua")

