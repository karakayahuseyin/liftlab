# Copyrigt (C) 2025 Hüseyin Karakaya
# This file is part of the LiftLab project and is licensed under the MIT License.

cmake_minimum_required(VERSION 3.10)
project(LiftLab LANGUAGES C CXX)

# C++17 standard requirement
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source and include directories
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Project source files
set(SOURCES
    # Core functionality
    "${SRC_DIR}/LiftLab.cpp"
    "${SRC_DIR}/core/Airfoil.cpp"
    "${SRC_DIR}/core/Wing.cpp"

    # Geometry components
    "${SRC_DIR}/geometry/NURBS.cpp"
    
    # Rendering components
    "${SRC_DIR}/renderer/Shader.cpp"
    "${SRC_DIR}/renderer/Renderer.cpp"

    # User interface components
    "${SRC_DIR}/gui/Window.cpp"
    "${SRC_DIR}/gui/ImGuiDrawer.cpp"

    # OpenGL initialization
    "${INCLUDE_DIR}/glad/glad.c"
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
find_package(OpenCASCADE REQUIRED)

# Handle OpenGL configuration for MinGW
if(MINGW)
    set(OpenGL_GL_PREFERENCE GLVND)
    find_package(OpenGL REQUIRED)
endif()

# Set include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR} ${SRC_DIR} ${OpenCASCADE_INCLUDE_DIR})

# Link ImGui, GLFW, and OpenGL libraries
target_link_libraries(imgui_backend imgui glfw OpenGL::GL)
target_link_libraries(${PROJECT_NAME} imgui_backend imgui glfw OpenGL::GL m ${OpenCASCADE_LIBRARIES})

message(STATUS "LiftLab project configuration complete.")