# Qt Two Buttons Application

A simple Qt application with two buttons that display message boxes when clicked.

## Prerequisites

- Qt6 development libraries
- CMake 3.16 or higher
- C++17 compatible compiler

## Building the Application

### Using CMake

1. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```

2. Configure the project:
   ```bash
   cmake ..
   ```

3. Build the project:
   ```bash
   cmake --build .
   ```

### Using qmake (Alternative)

If you prefer using qmake, you can create a .pro file and build with:
```bash
qmake
make
```

## Running the Application

After building, run the executable:
```bash
./bin/QtTwoButtonsApp  # On Linux/macOS
QtTwoButtonsApp.exe    # On Windows
```

## Features

- Two buttons that display different message boxes when clicked
- Clean, modern Qt6 interface
- Responsive layout using QVBoxLayout and QHBoxLayout

## Project Structure

- `main.cpp` - Main application source code
- `CMakeLists.txt` - CMake build configuration
- `README.md` - This file
