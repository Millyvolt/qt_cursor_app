@echo off
echo Opening mainwindow.ui in Qt Designer...
echo.

echo Looking for Qt Designer...
set DESIGNER_PATH=

REM Try common Qt Designer locations
if exist "C:\Qt\6.6.0\msvc2019_64\bin\designer.exe" (
    set DESIGNER_PATH=C:\Qt\6.6.0\msvc2019_64\bin\designer.exe
) else if exist "C:\Qt\6.5.0\msvc2019_64\bin\designer.exe" (
    set DESIGNER_PATH=C:\Qt\6.5.0\msvc2019_64\bin\designer.exe
) else if exist "C:\Qt\6.4.0\msvc2019_64\bin\designer.exe" (
    set DESIGNER_PATH=C:\Qt\6.4.0\msvc2019_64\bin\designer.exe
) else if exist "C:\Qt\6.3.0\msvc2019_64\bin\designer.exe" (
    set DESIGNER_PATH=C:\Qt\6.3.0\msvc2019_64\bin\designer.exe
) else if exist "C:\Qt\6.2.0\msvc2019_64\bin\designer.exe" (
    set DESIGNER_PATH=C:\Qt\6.2.0\msvc2019_64\bin\designer.exe
) else if exist "C:\Qt\6.1.0\msvc2019_64\bin\designer.exe" (
    set DESIGNER_PATH=C:\Qt\6.1.0\msvc2019_64\bin\designer.exe
) else if exist "C:\Qt\6.0.0\msvc2019_64\bin\designer.exe" (
    set DESIGNER_PATH=C:\Qt\6.0.0\msvc2019_64\bin\designer.exe
)

if "%DESIGNER_PATH%"=="" (
    echo Qt Designer not found in common locations.
    echo Please install Qt or provide the path to designer.exe
    echo.
    echo You can also try:
    echo 1. Install Qt from https://www.qt.io/download
    echo 2. Or use Qt Creator which includes Qt Designer
    echo 3. Or manually specify the path to designer.exe
    pause
    exit /b 1
)

echo Found Qt Designer at: %DESIGNER_PATH%
echo Opening mainwindow.ui...
echo.

"%DESIGNER_PATH%" mainwindow.ui

if %ERRORLEVEL% NEQ 0 (
    echo Failed to open Qt Designer
    pause
) else (
    echo Qt Designer opened successfully
)

