project "ImGuiLib"
    kind "StaticLib"
    language "C++"
    targetdir ("%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}")
    objdir ("%{wks.location}/bin-int/%{cfg.buildcfg}/%{prj.name}")


    files {
        "imgui/**.cpp",
        "imgui/**.h"
    }

    includedirs { "imgui" }
