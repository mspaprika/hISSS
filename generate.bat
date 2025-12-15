@echo off
set PROJECT_ROOT_DIR=%~dp0

pushd %PROJECT_ROOT_DIR%

"ext\premake\premake5.exe" vs2022

popd
pause