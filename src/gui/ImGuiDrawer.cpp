// Copyrigt (C) 2025 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#include "gui/ImGuiDrawer.h"

#include <iostream>

ImGuiDrawer::ImGuiDrawer(GLFWwindow* window) : window(window) 
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

ImGuiDrawer::~ImGuiDrawer() 
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiDrawer::beginFrame() 
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiDrawer::render() 
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiDrawer::endFrame() 
{
    glfwPollEvents();
}

void ImGuiDrawer::drawInfoPanel(float& zoom, glm::vec3& cameraPos, bool& exitRequested) 
{
    ImGui::SetNextWindowPos(ImVec2(15, 15));
    ImGui::SetNextWindowSize(ImVec2(250, 200));
    ImGui::Begin("Window", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("Camera Controls:");
    ImGui::SliderFloat("Zoom", &zoom, 1.0f, 45.0f);
    ImGui::Text("Position: (%.1f, %.1f, %.1f)", cameraPos.x, cameraPos.y, cameraPos.z);
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::Separator();
    ImGui::Separator();
    if (ImGui::Button("Exit")) {
        exitRequested = true;
    }
    ImGui::End();
}

void ImGuiDrawer::drawWingPanel(NURBSRenderer* renderer) 
{
    ImGui::SetNextWindowPos(ImVec2(15, 230));
    ImGui::SetNextWindowSize(ImVec2(250, 250));
    ImGui::Begin("Wing", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImGui::End();
}

