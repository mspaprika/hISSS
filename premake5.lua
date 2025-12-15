-------------------------------------------------------------
-- Name: Nth2 Workspace
-------------------------------------------------------------
nth = require "Tools/hisss_premake_module"

-- Top-level workspace premake
workspace "hiSSS_workspace"
    language "C++"
    location("Build/")          -- folder for generated .sln and .vcxproj
    platforms { "WIN_DX11" }   -- only DX11 / x64
    configurations { "Debug", "Debug_ASan", "Release" }

    -- Absolute path to workspace root
    local workspace_root = path.getabsolute(".")
    local hiSSS_include = path.join(workspace_root, "hiSSS/include")
    includedirs { hiSSS_include, ".", "../" }  -- hiSSS first, then local includes

    -- Common compiler settings
    filter {}
        cppdialect "C++20"
        warnings "High"
        flags { "FatalCompileWarnings", "MultiProcessorCompile" }
        characterset "Unicode"

    filter "configurations:Debug"
        defines { "DEBUG" }

    filter "configurations:Debug_ASan"
        defines { "DEBUG_ASAN" }

    filter "configurations:Release"
        defines { "NDEBUG" }


-- Include external libraries / projects
group("Play3D")
include(path.join("hiSSS/ext/Play3D/premake5.lua"))

group("Engine")
include("hiSSS/premake5.lua")

group("Game Libs")
include("SandBoxLib/premake5.lua")

group("Apps")
include("SandBox/premake5.lua")

---

-------------------------------------------------------------
-- workspace "hiSSS"
--     language "C++"
-- 	platforms {"WIN_DX11"}
-- 	configurations { "Debug", "Debug_ASan", "Release"}

--     local workspace_root = path.getabsolute(".")  -- your workspace root folder
--     local hiSSS_include = path.join(workspace_root, "hiSSS/include")
--     includedirs { hiSSS_include, ".", "../" }  -- hiSSS first, then local includes

--     includedirs { ".", "../" }
    
    
--     filter{}
--     language "C++"
--     cppdialect "C++20"
--     warnings "High"
--     flags { "FatalCompileWarnings","MultiProcessorCompile"}
    
--     characterset "Unicode"
--     location("Build/")
    
--     filter "configurations:Debug"
--     defines { "DEBUG"}
    

-- group("Play3D")
-- include ("hiSSS/ext/Play3D/premake5.lua")

-- group("Engine")
-- include ("hiSSS/premake5.lua")

-- group("Game Libs")
-- include ("SandBoxLib/premake5.lua")

-- group("Apps")
-- include ("SandBox/premake5.lua")




