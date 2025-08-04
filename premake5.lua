workspace "hiSSS"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "hiSSS"
    location "hiSSS"
    kind "SharedLib"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    
    vpaths {
        ["Source/hiSSS"] = { "hiSSS/src/hiSSS/**"},
        ["Source/include"] = { "hiSSS/src/include/**"},
        ["Source"] = { "hiSSS/src/**" },
    }

    includedirs
    {
        -- logger
         "%{prj.name}/ext/Play3D",
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "HS_PLATFORM_WINDOWS", "HS_BUILD_DLL"
            -- other macros
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.abspath} %{wks.location}/bin/" .. outputdir .. "/Sandbox")
        }


    filter "configurations:Debug"
        defines "HS_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "HS_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "HS_DIST"
        optimize "On"

    
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    vpaths
    {
        ["Source"] = "Sandbox/src/**",
    }

    includedirs
    {
        -- logger
        "hiSSS/src/include"
    }

    links
    {
        "hiSSS"
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

    filter "configurations:Debug"
        defines "HS_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "HS_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "HS_DIST"
        optimize "On"

