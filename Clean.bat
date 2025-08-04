
echo Cleaning intermediate build folders...

:: Delete intermediate binary and build folders
rmdir /S /Q bin
rmdir /S /Q bin-int

del /Q *.sln

cd hiSSS
del /Q *.vcxproj
del /Q *.vcxproj.filters

cd ..
cd Sandbox
del /Q *.vcxproj
del /Q *.vcxproj.filters
del /Q *.vcxproj.user
cd ..

pause