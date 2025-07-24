project "App"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++20"
    targetdir ("%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}")
    objdir ("%{wks.location}/bin-int/%{cfg.buildcfg}/%{prj.name}")

    files {
        "**.h",
        "**.cpp"
    }

    includedirs {
        "Data",
        "%{wks.location}/Engine/HissCoreLib",
        "%{wks.location}/Engine/ImGuiLib"
    }

    links {
        "Engine"
    }
