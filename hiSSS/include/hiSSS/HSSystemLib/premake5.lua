-------------------------------------------------------------
-- Name: RecognEyesLib
-- Description: Library that contains most of the game code
-------------------------------------------------------------
project "HSSystemLib"
	kind "StaticLib"
	architecture "x64"
		
	files {
		"premake5.lua",
		"**.cpp",
		"**.h",
		"**.natvis"
	}
	
	--nth.AddFiles()
	
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
        path.join(workspace_root, "hiSSS/include/ext/Play3D")
    }

	targetdir (path.join(workspace_root, "Build/bin/%{cfg.platform}/%{cfg.buildcfg}"))
    objdir (path.join(workspace_root, "Build/obj/%{cfg.platform}/%{cfg.buildcfg}"))

	debugdir "."