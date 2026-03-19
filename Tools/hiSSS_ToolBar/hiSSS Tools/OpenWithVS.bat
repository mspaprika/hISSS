set rootpath=%~dp0..\..\..\
pushd %rootpath%
:: %VS2022INSTALLDIR%
start "%VS2022INSTALLDIR%\Common7\IDE\devenv.exe" Build/hiSSS_workspace.sln
popd