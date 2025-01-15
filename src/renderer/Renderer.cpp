// Copyrigt (C) 2025 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#include "renderer/Renderer.h"

#include <glm/gtc/type_ptr.hpp>
   
Renderer::Renderer() {}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Renderer::initialize()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Renderer::render(glm::mat4 view, glm::mat4 projection)
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, vertices.size() / 3);
}

void Renderer::clear()
{
    // vertices.clear();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Renderer::loadVertices(const std::vector<float>& vertices)
{
    this->vertices = vertices;
}