# Copyrigt (C) 2025 Hüseyin Karakaya
# This file is part of the LiftLab project and is licensed under the MIT License.

cmake_minimum_required(VERSION 3.10)
project(LiftLab LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external")

# Project source files
set(SOURCES
    # Main entry point
    "${SRC_DIR}/LiftLab.cpp"

    # Core functionality
    "${SRC_DIR}/core/Airfoil.cpp"
    "${SRC_DIR}/core/Wing.cpp"

    # Geometry components
    "${SRC_DIR}/geometry/NURBS.cpp"
    
    # Rendering components
    "${SRC_DIR}/renderer/Shader.cpp"
    "${SRC_DIR}/renderer/Renderer.cpp"

    # User interface components
    "${SRC_DIR}/gui/Window.cpp"
    "${SRC_DIR}/gui/Drawer.cpp"

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

include(cmake/FindDependencies.cmake)

target_link_libraries(imgui_backend imgui glfw OpenGL::GL)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${INCLUDE_DIR} 
    ${SRC_DIR} 
    ${OpenCASCADE_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} 
    imgui_backend 
    imgui glfw 
    OpenGL::GL 
    m 
    ${OpenCASCADE_LIBRARIES}
)

message(STATUS "LiftLab project configuration complete.")

add_executable(${PROJECT_NAME}_tests
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp"
)

target_include_directories(${PROJECT_NAME}_tests PRIVATE 
    ${INCLUDE_DIR} 
    ${INCLUDE_DIR}/doctest/doctest 
    ${SRC_DIR} 
    ${OpenCASCADE_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}_tests 
    imgui_backend 
    imgui 
    glfw 
    OpenGL::GL 
    m 
    ${OpenCASCADE_LIBRARIES}
)

enable_testing()
add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}_tests)