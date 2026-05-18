@echo off
setlocal enabledelayedexpansion

if "%~1"=="" (
    echo Usage: new ^<ten_bai^>
    echo   VD:  new 1_two_sum
    echo   VD:  new 146_lru_cache
    exit /b 1
)

set "NAME=%~1"
if not "!NAME:~-4!"==".cpp" set "NAME=!NAME!.cpp"

if exist "!NAME!" (
    echo File da ton tai: !NAME!
    exit /b 1
)

copy template.cpp "!NAME!" >nul
echo Tao file: !NAME!

:: Mo bang editor dau tien tim thay
where code >nul 2>&1
if not errorlevel 1 ( code "!NAME!" & exit /b 0 )
where nvim >nul 2>&1
if not errorlevel 1 ( nvim "!NAME!" & exit /b 0 )
where vim >nul 2>&1
if not errorlevel 1 ( vim "!NAME!" & exit /b 0 )
notepad "!NAME!"
