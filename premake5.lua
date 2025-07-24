workspace "Hisss"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "Game/App"

group ("Engine")
include ("Engine/premake5.lua")

group ("Engine/ImGuiLib")
include ("Engine/ImGuiLib/premake5.lua")

group ("Engine/HissCoreLib")
include ("Engine/HissCoreLib/premake5.lua")

group ("Engine/HissCoreLib/Play3D")
include ("Engine/HissCoreLib/Play3D/premake5.lua")

group ("Game/App")
include ("Game/App/premake5.lua")