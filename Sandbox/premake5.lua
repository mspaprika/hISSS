-------------------------------------------------------------
-- Name: RecognEyesGame
-- Description: Main Game Application
-------------------------------------------------------------
project "SandBoxApp"
	kind "WindowedApp"
	platforms {"WIN_DX11"}
	language "C++"
	architecture "x64"
	
	nth.AddFiles()
	filter {}
	
	filter "system:windows"
	cppdialect "C++20"
	staticruntime "On"
	systemversion "latest"
	
	defines
	{
		"HS_PLATFORM_WINDOWS", 
		-- macros
	}
	
	-- links 
	-- {
	-- 	"Play3D",
	-- 	"hiSSS", "HSHeaderLib", "HSSystemLib"
	-- }

	local workspace_root = path.getabsolute("..")

	libdirs {
		path.join(workspace_root, "Build/bin/WIN_DX11/Debug"),  -- .lib output folder
		path.join(workspace_root, "Build/bin/WIN_DX11/Release")
	}
	
	links { "hiSSS", "HSHeaderLib", "HSSystemLib", "SandBoxLib", "Play3D" }
    dependson { "hiSSS", "HSHeaderLib", "SandBoxLib", "HSSystemLib", "Play3D" }
	
	
	nth.AddMainProjectSettings()