// Copyrigt (C) 2025 Hüseyin Karakaya
// This file is part of the liftlab project and is licensed under the MIT License.

#include <iostream>

#include "liftlab/ui/window.h"

Window* globalInstance = nullptr;

Window::Window()
    : width(1200), height(800), title("LiftLab"),
      cameraPos(0.0f, 0.0f, 5.0f), cameraFront(0.0f, 0.0f, -1.0f), cameraUp(0.0f, 1.0f, 0.0f),
      yaw(-90.0f), pitch(0.0f), zoom(45.0f), leftMousePressed(false), rightMousePressed(false),
      lastX(width / 2.0), lastY(height / 2.0), cameraSpeed(0.01f) 
{
    cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
    globalInstance = this;
    imguiDrawer = nullptr;
    renderer = nullptr;
}

Window::~Window() 
{
    delete globalInstance;
    delete imguiDrawer;
    delete renderer;
}

void Window::create() 
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetKeyCallback(window, keyCallback);

    glEnable(GL_DEPTH_TEST);

    shaderProgram = compileShader();

    imguiDrawer = new ImGuiDrawer(window);
    renderer = new NURBSRenderer();

    renderer->initialize();
}

void Window::render() 
{
    bool exitRequested = false;
    glm::mat4 model = glm::mat4(1.0f);

    while (!glfwWindowShouldClose(window) && !exitRequested) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        imguiDrawer->beginFrame(); // ImGui çerçevesi başlat
        imguiDrawer->drawInfoPanel(zoom, cameraPos, exitRequested); // Kontrol paneli çiz
        imguiDrawer->drawWingPanel(renderer); // Kanat panelini çiz
        imguiDrawer->render(); // ImGui'yi OpenGL'e render et

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 projection = glm::perspective(glm::radians(zoom), static_cast<float>(width) / height, 0.1f, 100.0f);

        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        renderer->render(view, projection);
        imguiDrawer->endFrame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete imguiDrawer;
    delete renderer;
    glfwTerminate();
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    if (key == GLFW_KEY_X && action == GLFW_PRESS) {
        std::cerr << "X key pressed. Closing window..." << std::endl;
        glfwSetWindowShouldClose(window, true);
    }
}

void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) 
{
    globalInstance->processMouseButton(button, action);
}

void Window::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) 
{
    globalInstance->processMouseMovement(xpos, ypos);
}

void Window::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) 
{
    globalInstance->processMouseScroll(yoffset);
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) 
{
    glViewport(0, 0, width, height);
}

void Window::processMouseMovement(double xpos, double ypos) 
{
    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    if (leftMousePressed) {
        const float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        updateCameraVectors();
    }

    if (rightMousePressed) {
        cameraPos -= cameraRight * static_cast<float>(xoffset * cameraSpeed);
        cameraPos -= cameraUp * static_cast<float>(yoffset * cameraSpeed);
    }
}

void Window::processMouseScroll(double yoffset) 
{
    zoom -= yoffset;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
}

void Window::processMouseButton(int button, int action) 
{
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        leftMousePressed = (action == GLFW_PRESS);
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        rightMousePressed = (action == GLFW_PRESS);
    }
}

void Window::updateCameraVectors() 
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
    cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
}