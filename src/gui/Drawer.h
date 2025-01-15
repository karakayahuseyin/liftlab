// Copyrigt (C) 2025 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#ifndef DRAWER_H
#define DRAWER_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "core/Wing.h"
#include "renderer/Renderer.h"

class Drawer {
public:
    Drawer(GLFWwindow* window);
    ~Drawer();

    void beginFrame();
    void render();
    void endFrame();
    // Call drawInfoPanel, drawWingPanel, etc.
    void addDraw(void (*drawFunction)(Renderer*)); 

    void drawInfoPanel(float& zoom, glm::vec3& cameraPos, bool& exitRequested);
    void drawWingPanel(Renderer* renderer);
private:
    GLFWwindow* window;
};

#endif // DRAWER_H
