project "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    targetdir ("%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}")
    objdir ("%{wks.location}/bin-int/%{cfg.buildcfg}/%{prj.name}")

    files {
        "HissCoreLib/**.h",
        "ImGuiLib/**.cpp"
    }

    includedirs {
        "%{wks.location}/Engine/ImGuiLib",
        "%{wks.location}/Engine/HissCoreLib"
    }

    links {
        "ImGuiLib",
        "HissCoreLib"
    }
