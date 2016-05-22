@echo off

if "%1" == "-tp" (
    cd build
    mkdir ThirdParty
    cd ThirdParty

    REM Build the dependencies. (SDL2, Assimp)

    cmake ../../ExampleCommon/ThirdParty/ -G "Visual Studio 14 2015 Win64" -DDIRECTX=NO -DASSIMP_BUILD_ASSIMP_TOOLS=NO
    msbuild.exe ThirdParty.sln /p:Configuration=Debug
    msbuild.exe ThirdParty.sln /p:Configuration=Release
) else (

    REM Copy dependency DLLs to bin
    copy /Y ExampleCommon\ThirdParty\lib\SDL2\bin\Debug\SDL2.dll bin\Debug
    copy /Y ExampleCommon\ThirdParty\lib\assimp\bin\Debug\assimp.dll bin\Debug
    copy /Y %VK_SDK_PATH%\Source\lib\*.dll bin\Debug

    copy /Y ExampleCommon\ThirdParty\lib\SDL2\bin\Release\SDL2.dll bin\Release
    copy /Y ExampleCommon\ThirdParty\lib\assimp\bin\Release\assimp.dll bin\Release
    copy /Y %VK_SDK_PATH%\Bin\*.dll bin\Release

    REM Generate the Visual Studio solution for Vulkan tests
    cd build
    cmake ../ -G "Visual Studio 14 2015 Win64"
)
