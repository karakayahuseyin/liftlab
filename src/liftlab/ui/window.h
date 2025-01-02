// Copyrigt (C) 2025 Hüseyin Karakaya
// This file is part of the liftlab project and is licensed under the MIT License.

#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "liftlab/renderer/nurbs_renderer.h"
#include "liftlab/renderer/shader.h"
#include "liftlab/ui/imgui_drawer.h"

class Window {
public:
    Window();
    ~Window();

    void create();
    void render();

private:
    int width;
    int height;
    std::string title;

    GLFWwindow* window;
    unsigned int shaderProgram;

    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;

    float yaw;
    float pitch;
    float zoom;
    bool leftMousePressed;
    bool rightMousePressed;
    double lastX;
    double lastY;
    float cameraSpeed;

    NURBSRenderer* renderer;
    Gui* gui;

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

    void processMouseMovement(double xpos, double ypos);
    void processMouseScroll(double yoffset);
    void processMouseButton(int button, int action);
    void updateCameraVectors();
};

#endif // WINDOW_H