@echo off
echo ========================================
echo Qt UI Debug Information
echo ========================================
echo.

echo Current Directory: %CD%
echo.

echo Checking for UI files:
if exist "mainwindow.ui" (
    echo ✓ mainwindow.ui found in current directory
    echo   Size: %~z1 mainwindow.ui bytes
) else (
    echo ✗ mainwindow.ui NOT found in current directory
)

if exist "styles.qss" (
    echo ✓ styles.qss found in current directory
    echo   Size: %~z1 styles.qss bytes
) else (
    echo ✗ styles.qss NOT found in current directory
)

echo.

echo Checking build directory:
if exist "build\bin\mainwindow.ui" (
    echo ✓ mainwindow.ui found in build/bin/
) else (
    echo ✗ mainwindow.ui NOT found in build/bin/
)

if exist "build\bin\styles.qss" (
    echo ✓ styles.qss found in build/bin/
) else (
    echo ✗ styles.qss NOT found in build/bin/
)

echo.

echo Checking Qt installation:
set QT_FOUND=false
for /d %%i in ("C:\Qt\*") do (
    if exist "%%i\msvc2019_64\bin\designer.exe" (
        echo ✓ Qt Designer found: %%i\msvc2019_64\bin\designer.exe
        set QT_FOUND=true
    )
    if exist "%%i\msvc2022_64\bin\designer.exe" (
        echo ✓ Qt Designer found: %%i\msvc2022_64\bin\designer.exe
        set QT_FOUND=true
    )
)

if "%QT_FOUND%"=="false" (
    echo ✗ Qt Designer not found in common locations
)

echo.

echo Checking for QUiLoader support:
if exist "C:\Qt\6.6.0\msvc2019_64\bin\Qt6UiTools.dll" (
    echo ✓ Qt6UiTools.dll found
) else if exist "C:\Qt\6.5.0\msvc2019_64\bin\Qt6UiTools.dll" (
    echo ✓ Qt6UiTools.dll found
) else if exist "C:\Qt\6.4.0\msvc2019_64\bin\Qt6UiTools.dll" (
    echo ✓ Qt6UiTools.dll found
) else (
    echo ✗ Qt6UiTools.dll not found - this may cause UI loading issues
)

echo.

echo ========================================
echo Building and Running Application
echo ========================================
echo.

if not exist build mkdir build
cd build

echo Running CMake...
cmake .. -DCMAKE_BUILD_TYPE=Debug
if %ERRORLEVEL% NEQ 0 (
    echo ✗ CMake failed
    pause
    exit /b 1
)

echo.
echo Building application...
cmake --build . --config Debug
if %ERRORLEVEL% NEQ 0 (
    echo ✗ Build failed
    pause
    exit /b 1
)

echo.
echo ========================================
echo Running Application with Debug Output
echo ========================================
echo.

echo The application will now run with debug output.
echo Look for messages about UI loading and file paths.
echo.

cd bin
QtTwoButtonsApp.exe

echo.
echo Application finished.
pause

