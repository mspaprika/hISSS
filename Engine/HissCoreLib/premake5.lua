project "HissCoreLib"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    targetdir ("%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}")
    objdir ("%{wks.location}/bin-int/%{cfg.buildcfg}/%{prj.name}")

    files {
        "Play3D/**.h",
        "Play3D/**.cpp"
    }

    includedirs {
        "%{wks.location}/Engine/HissCoreLib/Play3D",
    }

    links {
        "ImGuiLib",
    }
