@echo off
echo Building and running Qt application with stylesheet debugging...
echo.

echo Current directory: %CD%
echo Checking for styles.qss in current directory...
if exist styles.qss (
    echo ✓ styles.qss found in current directory
) else (
    echo ✗ styles.qss not found in current directory
)

echo.
echo Building with CMake...
if not exist build mkdir build
cd build
cmake ..
cmake --build .

echo.
echo Running application...
echo (Check the console output for stylesheet loading messages)
echo.
./bin/QtTwoButtonsApp.exe

pause
