// Copyrigt (C) 2024 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <filesystem>
#include <cmath>

#include "nurbs_renderer.h"

using namespace Nurbs;
   
NURBSRenderer::NURBSRenderer() {}

void NURBSRenderer::addSurface(const Nurbs::Surface* surface)
{
    surfaces.push_back(surface);
}

void NURBSRenderer::initialize()
{
    for (const Nurbs::Surface* surface : surfaces) {
        generateSurfaceMesh(surface);
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void NURBSRenderer::generateSurfaceMesh(const Surface* surface)
{
    const int resolutionU = 100, resolutionV = 10;
    for (int i = 0; i <= resolutionU; ++i) {
        double u = i / (double)resolutionU;
        for (int j = 0; j <= resolutionV; ++j) {
            double v = j / (double)resolutionV;
            Nurbs::Point3D point = Nurbs::evaluateSurface(surface, u, v);
            vertices.push_back(point.x);
            vertices.push_back(point.y);
            vertices.push_back(point.z);
        }
    }
    // Last indices for the each surface
    surfaceIndices.push_back(vertices.size() / 3);
}

void NURBSRenderer::render(glm::mat4 view, glm::mat4 projection)
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, vertices.size() / 3);
}

NURBSRenderer::~NURBSRenderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void NURBSRenderer::exportSurfaces()
{
    std::string outputDir = "/home/huseyin/dev/wing-generator-project/wing-generator/build/";
    for (size_t i = 0; i < surfaceIndices.size(); ++i) {
        std::string filename = outputDir + "surface" + std::to_string(i + 1) + ".obj";
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            continue;
        }
        std::cout << "Writing to file: " << filename << std::endl;

        size_t startIdx = (i == 0) ? 0 : surfaceIndices[i - 1];
        size_t endIdx = surfaceIndices[i];
        size_t resolutionU = 100, resolutionV = 10;

        // Write vertices
        for (size_t idx = startIdx; idx < endIdx; ++idx) {
            outFile << "v " << vertices[idx * 3] << " "
                    << vertices[idx * 3 + 1] << " "
                    << vertices[idx * 3 + 2] << "\n";
        }

        // Write faces
        for (size_t u = 0; u < resolutionU; ++u) {
            for (size_t v = 0; v < resolutionV; ++v) {
                size_t idx1 = startIdx + u * (resolutionV + 1) + v;
                size_t idx2 = startIdx + (u + 1) * (resolutionV + 1) + v;
                size_t idx3 = startIdx + (u + 1) * (resolutionV + 1) + (v + 1);
                size_t idx4 = startIdx + u * (resolutionV + 1) + (v + 1);

                outFile << "f " << idx1 + 1 << " " << idx2 + 1 << " "
                        << idx3 + 1 << " " << idx4 + 1 << "\n";
            }
        }

        outFile.close();
    }
}

