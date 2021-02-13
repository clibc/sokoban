@echo off

set files=..\src\*.c
set flags=/W3 /nologo /Fe.\a.exe /EHsc /Zi /MP6
set libs=opengl32.lib ..\dependencies\GLFW\libs\glfw3dll.lib
set includes=/I ..\dependencies\ /I ..\src\

if not exist output\ (
   mkdir output\
)

pushd output
    cl %flags% %files% %includes% /link %libs% /SUBSYSTEM:CONSOLE
popd 
