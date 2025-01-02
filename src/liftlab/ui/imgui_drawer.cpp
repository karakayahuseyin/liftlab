// Copyrigt (C) 2025 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#include <iostream>
#include "liftlab/ui/imgui_drawer.h"

Gui::Gui(GLFWwindow* window) : window(window) 
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

Gui::~Gui() 
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Gui::beginFrame() 
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Gui::render() 
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::endFrame() 
{
    glfwPollEvents();
}

void Gui::drawInfoPanel(float& zoom, glm::vec3& cameraPos, bool& exitRequested) 
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

double span, chord;
int airfoilNum;

void Gui::drawWingPanel(NURBSRenderer* renderer) 
{
    ImGui::SetNextWindowPos(ImVec2(15, 230));
    ImGui::SetNextWindowSize(ImVec2(250, 250));
    ImGui::Begin("Wing", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("Wing Parameters:");
    ImGui::InputInt("Airfoil", &airfoilNum);
    ImGui::InputDouble("Span" , &span);
    ImGui::InputDouble("Chord" , &chord);
    if (ImGui::Button("Generate Wing")) {
        double M = airfoilNum / 1000.0;
        double P = (airfoilNum / 100) % 10;
        double T = airfoilNum % 100;
        Airfoil airfoil(M, P, T);
        Wing newWing(airfoil, span, chord);
        std::vector<Nurbs::Surface*> surfaces = newWing.generate();
        if (surfaces.empty() || !surfaces[0]) {
            throw std::runtime_error("Failed to generate surfaces");
        }
        renderer->clear();
        for (Nurbs::Surface* surface : surfaces) {
            renderer->addSurface(surface);
            std::cout << "Surface added" << std::endl;
        }
        renderer->initialize();
    }
    if (ImGui::Button("Export Surfaces")) {
        renderer->exportSurfaces();
    }
    ImGui::Text("Surface Parameters:");
    // ImGui::SliderInt("U Resolution", &renderer->uResolution, 1, 100);
    // ImGui::SliderInt("V Resolution", &renderer->vResolution, 1, 100);
    ImGui::Separator();
    ImGui::Text("Surface Display:");
    // ImGui::Checkbox("Control Points", &renderer->showControlPoints);
    // ImGui::Checkbox("Control Net", &renderer->showControlNet);
    // ImGui::Checkbox("Surface", &renderer->showSurface);
    ImGui::End();
}

