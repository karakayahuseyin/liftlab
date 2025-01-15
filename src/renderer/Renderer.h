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

#include "geometry/NURBS.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void initialize();
    void loadVertices(const std::vector<float>& vertices);
    void render(glm::mat4 view, glm::mat4 projection);
    void clear();

private:
    unsigned int VAO, VBO;
    std::vector<float> vertices;
};

#endif // NURBS_RENDERER_H
