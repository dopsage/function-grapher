cmake_minimum_required(VERSION 3.10)
project(FunctionGrapher VERSION 1.0.0 LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "SFML_DIR = ${SFML_DIR}")
message(STATUS "SFML_FOUND = ${SFML_FOUND}")

# Find SFML (version 2.6.1 or higher); look for `graphics`, `window` and `system` modules
find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

# Add executable
add_executable(function_grapher src/Main.cpp src/SGF/Canvas.cpp src/SGF/Rectangle.cpp)

# Include local headers
target_include_directories(function_grapher PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link SFML libraries
target_link_libraries(function_grapher sfml-graphics sfml-window sfml-system)
