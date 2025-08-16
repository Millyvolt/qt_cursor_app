cmake_minimum_required(VERSION 3.16)

project(QtTwoButtonsApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets UiTools)

# Enable automoc for Qt
set(CMAKE_AUTOMOC ON)

# Create executable
add_executable(QtTwoButtonsApp main.cpp)

# Link Qt libraries
target_link_libraries(QtTwoButtonsApp Qt6::Core Qt6::Widgets Qt6::UiTools)

# Set output directory
set_target_properties(QtTwoButtonsApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Copy styles.qss to build directory
configure_file(${CMAKE_SOURCE_DIR}/styles.qss ${CMAKE_BINARY_DIR}/bin/styles.qss COPYONLY)

# Copy UI file to build directory
configure_file(${CMAKE_SOURCE_DIR}/mainwindow.ui ${CMAKE_BINARY_DIR}/bin/mainwindow.ui COPYONLY)
