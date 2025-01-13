// Copyrigt (C) 2025 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#pragma once

#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>
#include <string>

extern const char* vertexShaderSource;

extern const char* fragmentShaderSource;

unsigned int compileShader();

#endif // SHADERS_H