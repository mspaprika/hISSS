@echo off
setlocal
set rootpath=%~dp0..\..\
pushd %rootpath%

set AssetTool=Tools\Play3dAssetTool.exe



%AssetTool% gltf SourceAssets/UFO/UFO.glb --scale 1.0

pause