# Copyrigt (C) 2024 Hüseyin Karakaya
# This file is part of the liftlab project and is licensed under the MIT License.

cmake_minimum_required(VERSION 3.10)
project(liftlab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR 
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

set(INCLUDE_DIRECTORIES 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

set(SOURCES
    "${SRC_DIR}/main.cpp"
    "${SRC_DIR}/airfoil.cpp"
    "${SRC_DIR}/wing.cpp"
    "${SRC_DIR}/gui.cpp"
    "${SRC_DIR}/nurbs.cpp"
    "${SRC_DIR}/shaders.cpp"
    "${SRC_DIR}/nurbs_renderer.cpp"
    "${SRC_DIR}/window.cpp"
    "${INCLUDE_DIRECTORIES}/glad/glad.c"
)

# Executable creation
add_executable(${PROJECT_NAME} ${SOURCES})

# ImGui library
add_library(imgui STATIC
    ${INCLUDE_DIRECTORIES}/imgui/imgui.cpp
    ${INCLUDE_DIRECTORIES}/imgui/imgui_draw.cpp
    ${INCLUDE_DIRECTORIES}/imgui/imgui_demo.cpp
    ${INCLUDE_DIRECTORIES}/imgui/imgui_tables.cpp
    ${INCLUDE_DIRECTORIES}/imgui/imgui_widgets.cpp
)

target_include_directories(imgui PUBLIC ${INCLUDE_DIRECTORIES}/imgui)

# ImGui backend
add_library(imgui_backend STATIC
    ${INCLUDE_DIRECTORIES}/imgui/backends/imgui_impl_glfw.cpp
    ${INCLUDE_DIRECTORIES}/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui_backend PUBLIC
    ${INCLUDE_DIRECTORIES}/imgui
    ${INCLUDE_DIRECTORIES}/imgui/backends
)

# Find necessary libraries
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)

# OpenGL and other library setup for MinGW
if(MINGW)
    set(OpenGL_GL_PREFERENCE GLVND)
    find_package(OpenGL REQUIRED)
endif()

# Include directories for libraries
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRECTORIES} GLEW::GLEW)

# Link libraries
target_link_libraries(imgui_backend imgui glfw OpenGL::GL GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} imgui_backend imgui glfw OpenGL::GL m GLEW::GLEW)