cmake_minimum_required(VERSION 3.21)
project(owl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_SHARED_LIBRARIES ON)

add_subdirectory(vendor/glfw)
add_definitions(-DGLFW_INCLUDE_NONE)

include_directories(vendor/glad/include)
include_directories(vendor/glfw/include)
include_directories(include)

add_library(owl SHARED include/owl/Window.hpp src/Window.cpp vendor/glad/include/glad/glad.h vendor/glad/src/glad.c include/owl/Color.hpp src/Color.cpp src/Util.hpp include/owl/Vec2.hpp include/owl/Shader.hpp src/Shader.cpp include/owl/owl.hpp)

target_link_libraries(owl glfw)