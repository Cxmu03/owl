cmake_minimum_required(VERSION 3.21)
project(owl)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(vendor/glfw)
add_definitions(-DGLFW_INCLUDE_NONE)

include_directories(vendor/glad/include)
include_directories(vendor/glfw/include)

add_executable(owl "example/Simple_window/main.cpp" owl/Window.hpp owl/Window.cpp vendor/glad/include/glad/glad.h vendor/glad/src/glad.c owl/Color.hpp owl/Color.cpp owl/Util.hpp owl/Vec2.hpp owl/Shader.hpp owl/Shader.cpp owl/owl.hpp)

target_link_libraries(owl glfw)