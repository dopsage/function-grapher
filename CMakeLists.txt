cmake_minimum_required(VERSION 3.10)
project(FunctionGrapher VERSION 1.0.0 LANGUAGES CXX)

# Require C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML (version 2.5 or higher); look for `graphics`, `window` and `system` modules
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add executable
add_executable(function_grapher src/Main.cpp src/SGF/Canvas.cpp src/SGF/Rectangle.cpp)

# Include local headers
target_include_directories(function_grapher PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link SFML libraries
target_link_libraries(function_grapher sfml-graphics sfml-window sfml-system)
