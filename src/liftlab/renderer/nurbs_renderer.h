// Copyrigt (C) 2025 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#ifndef NURBS_RENDERER_H
#define NURBS_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "liftlab/renderer/nurbs.h"

class NURBSRenderer {
public:
    NURBSRenderer();
    ~NURBSRenderer();

    void addSurface(const Nurbs::Surface* surface);
    void initialize();
    void render(glm::mat4 view, glm::mat4 projection);
    void clear(); //
    void exportSurfaces();

private:
    void generateSurfaceMesh(const Nurbs::Surface* surface);
    
    std::vector<const Nurbs::Surface*> surfaces;
    unsigned int VAO, VBO;
    std::vector<float> vertices;
    std::vector<unsigned int> surfaceIndices;
};

#endif // NURBS_RENDERER_H
