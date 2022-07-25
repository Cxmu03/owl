cmake_minimum_required(VERSION 3.21)
project(owl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_SHARED_LIBRARIES ON)

add_subdirectory(vendor/glfw)
add_definitions(-DGLFW_INCLUDE_NONE)

add_subdirectory(vendor/glm)

add_library(owl STATIC include/owl/Window.hpp src/Window.cpp vendor/glad/include/glad/glad.h vendor/glad/src/glad.c include/owl/Color.hpp src/Color.cpp src/Util.hpp include/owl/Shader.hpp src/Shader.cpp include/owl/owl.hpp)

target_include_directories(owl PUBLIC vendor/glad/include)
target_include_directories(owl PUBLIC vendor/glfw/include)
target_include_directories(owl PUBLIC vendor/glm)
target_include_directories(owl PUBLIC include)

target_link_libraries(owl glfw)