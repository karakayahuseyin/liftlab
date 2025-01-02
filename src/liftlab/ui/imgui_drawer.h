// Copyrigt (C) 2025 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#ifndef GUI_H
#define GUI_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "liftlab/core/wing.h"
#include "liftlab/renderer/nurbs_renderer.h"

class Gui {
public:
    Gui(GLFWwindow* window);
    ~Gui();

    void beginFrame();
    void render();
    void endFrame();

    // Example function to add widgets
    void drawInfoPanel(float& zoom, glm::vec3& cameraPos, bool& exitRequested);
    void drawWingPanel(NURBSRenderer* renderer);

private:
    GLFWwindow* window;
};

#endif // GUI_H
