::
:: Created by Tech_dog (ebontrop@gmail.com) on 10-Apr-2021 at 11:27:22.019 am, UTC+7, Novosibirsk, Saturday;
:: This is Ebo Pack Shared Lite static library project x64 debug build script batch file;
:: Adopted to OpenGL tutorials' camera project om 17-May-2026 at 23:01:28.634, UTC+4, Batumi, Sunday;
::
@echo off

set v_current=%~dp0
set v_studio=C:\VS.15\
set v_source_base=%v_current%
set v_settings=%v_studio%VC\Auxiliary\Build\vcvars64.bat
set v_msbuild=%v_studio%MSBuild\15.0\Bin\MSBuild.exe

@echo.
@echo [INFO] Using the following settings:
@echo        Code base    : %v_source_base%
@echo        MS_Build_Exe : %v_msbuild%
@echo        Build mode   : x64::debug
@echo.

@echo [WARN] Build the executable...
call "%v_msbuild%" /t:build gl.tutor.3.camera.vcxproj /p:Configuration=Debug /p:Platform=x64

pause
exit