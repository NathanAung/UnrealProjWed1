@echo off

set thisPath=%cd%
if exist "C:\Program Files\Epic Games\UE_5.5\Engine\Build\BatchFiles\Build.bat" set compiler="C:\Program Files\Epic Games\UE_5.5\Engine\Build\BatchFiles\Build.bat"
if exist "D:\Program Files\Epic Games\UE_5.5\Engine\Build\BatchFiles\Build.bat" set compiler="D:\Program Files\Epic Games\UE_5.5\Engine\Build\BatchFiles\Build.bat"

set projExt=*.uproject

pushd %thisPath%
for %%a in (%projExt%) do set projName=%%a
popd

call %compiler% %projName:~0,-9%Editor Win64 Development "%thisPath%\%projName%" -waitmutex

pause