@echo off

set thisPath=%cd%

if exist "C:\Program Files\Epic Games\UE_5.5\Engine\Binaries\Win64\UnrealEditor.exe" set unreal="C:\Program Files\Epic Games\UE_5.5\Engine\Binaries\Win64\UnrealEditor.exe"
if exist "D:\Program Files\Epic Games\UE_5.5\Engine\Binaries\Win64\UnrealEditor.exe" set unreal="D:\Program Files\Epic Games\UE_5.5\Engine\Binaries\Win64\UnrealEditor.exe"

set projExt=*.uproject

pushd %thisPath%
for %%a in (%projExt%) do set projName=%%a
popd

%unreal% "%thisPath%\%projName%" -log -game -windowed -resx=1280 -resy=720