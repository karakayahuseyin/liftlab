// Copyright (C) 2025 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#pragma once

#include <glm/glm.hpp>

namespace Gui {

class InfoPanel {
public:
    InfoPanel();
    InfoPanel();

    void draw(float& zoom, glm::vec3& cameraPos, bool& exitRequested);

private:
    float zoom;
    glm::vec3 cameraPos;
    bool exitRequested;
};

} // namespace Gui