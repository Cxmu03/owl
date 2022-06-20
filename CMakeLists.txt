cmake_minimum_required(VERSION 3.21)
project(owl)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(vendor/glfw)
add_definitions(-DGLFW_INCLUDE_NONE)

include_directories(vendor/glad/include)
include_directories(vendor/glfw/include)

add_executable(owl example/main.cpp owl/Window.h owl/Window.cpp)
