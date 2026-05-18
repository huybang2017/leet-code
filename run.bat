@echo off
setlocal enabledelayedexpansion

set "FILE=%~1"

:: Khong truyen tham so -> lay file .cpp moi nhat
if "%FILE%"=="" (
    for /f "delims=" %%i in ('dir /b /o-d *.cpp 2^>nul') do (
        set "FILE=%%i"
        goto :compile
    )
    echo Khong tim thay file .cpp nao.
    exit /b 1
)

:: Chi la so (VD: 1, 146) -> tim file so_*.cpp
set "ISNUM="
for /f "delims=0123456789" %%i in ("%FILE%") do set "ISNUM=%%i"
if "!ISNUM!"=="" (
    for /f "delims=" %%i in ('dir /b "!FILE!_*.cpp" 2^>nul') do (
        set "FILE=%%i"
        goto :compile
    )
    set "FILE=!FILE!.cpp"
)

:compile
if not "!FILE:~-4!"==".cpp" set "FILE=!FILE!.cpp"

if not exist "!FILE!" (
    echo Khong tim thay: !FILE!
    exit /b 1
)

set "EXE=!FILE:.cpp=.exe!"

echo Compiling !FILE! ...
g++ -std=c++17 -O2 -Wall -o "!EXE!" "!FILE!"
if errorlevel 1 (
    echo Compile that bai!
    exit /b 1
)

echo Running...
echo.
call ".\!EXE!"
exit /b %errorlevel%
