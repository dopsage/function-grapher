cmake_minimum_required(VERSION 3.10)
project(FunctionGrapher VERSION 1.0.0 LANGUAGES CXX)

# Require C++11
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML (version 2.5 or higher); look for `graphics`, `window` and `system` modules
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add executable
set(PROJECT_EXEC function_grapher)
add_executable(
    ${PROJECT_EXEC}
    src/Main.cpp
    src/SGF/Button.cpp
    src/SGF/Canvas.cpp
    src/SGF/InputParser.cpp
    src/SGF/Rectangle.cpp
    src/SGF/ScrollView.cpp
    src/SGF/TextInput.cpp
    src/SGF/TextProperties.cpp
    src/FunctionEntry.cpp
    src/SGF/VList.cpp
    src/SGF/VSlider.cpp
)

# Copy resources next to the executable so it can use them
add_custom_command(
    TARGET ${PROJECT_EXEC} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
    "$<TARGET_FILE_DIR:${PROJECT_EXEC}>/res"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/res"
    "$<TARGET_FILE_DIR:${PROJECT_EXEC}>/res"
)

# Include local headers
target_include_directories(${PROJECT_EXEC} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link SFML libraries
target_link_libraries(${PROJECT_EXEC} sfml-graphics sfml-window sfml-system)
