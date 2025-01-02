# Copyrigt (C) 2025 Hüseyin Karakaya
# This file is part of the LiftLab project and is licensed under the MIT License.

cmake_minimum_required(VERSION 3.10)
project(liftlab LANGUAGES CXX)

# C++17 standard requirement
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source and include directories
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Project source files
set(SOURCES
    # Core functionality
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/liftlab/core/airfoil.cpp
    ${SRC_DIR}/liftlab/core/wing.cpp

    # Rendering components
    ${SRC_DIR}/liftlab/renderer/shader.cpp
    ${SRC_DIR}/liftlab/renderer/nurbs.cpp
    ${SRC_DIR}/liftlab/renderer/nurbs_renderer.cpp

    # User interface components
    ${SRC_DIR}/liftlab/ui/window.cpp
    ${SRC_DIR}/liftlab/ui/imgui_drawer.cpp

    # OpenGL initialization
    ${INCLUDE_DIR}/glad/glad.c
)

# Define the main executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Add ImGui library
add_library(imgui STATIC
    ${INCLUDE_DIR}/imgui/imgui.cpp
    ${INCLUDE_DIR}/imgui/imgui_draw.cpp
    ${INCLUDE_DIR}/imgui/imgui_demo.cpp
    ${INCLUDE_DIR}/imgui/imgui_tables.cpp
    ${INCLUDE_DIR}/imgui/imgui_widgets.cpp
)

target_include_directories(imgui PUBLIC ${INCLUDE_DIR}/imgui)

# Add ImGui backend
add_library(imgui_backend STATIC
    ${INCLUDE_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${INCLUDE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui_backend PUBLIC
    ${INCLUDE_DIR}/imgui
    ${INCLUDE_DIR}/imgui/backends
)

# Link required libraries
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)

# Handle OpenGL configuration for MinGW
if(MINGW)
    set(OpenGL_GL_PREFERENCE GLVND)
    find_package(OpenGL REQUIRED)
endif()

# Set include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR} ${SRC_DIR} GLEW::GLEW)

# Link ImGui, GLFW, and OpenGL libraries
target_link_libraries(imgui_backend imgui glfw OpenGL::GL GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} imgui_backend imgui glfw OpenGL::GL m GLEW::GLEW)

message(STATUS "LiftLab project configuration complete.")