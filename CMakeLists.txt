cmake_minimum_required(VERSION 3.21)
project(OWL)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(vendor/glfw)
add_definitions(-DGLFW_INCLUDE_NONE)

include_directories(vendor/glad/include)

add_executable(OWL src/main.cpp)
