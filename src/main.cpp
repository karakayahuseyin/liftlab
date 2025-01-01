// Copyrigt (C) 2024 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#include <vector>
#include <iostream>
#include <fstream>

#include "window.h"
#include "nurbs_renderer.h"
#include "wing.h"

Wing* wing;

int main() 
{

    int fourDigitInput = 2412;
    double M = fourDigitInput / 1000.0;
    double P = (fourDigitInput / 100) % 10;
    double T = fourDigitInput % 100;

    Airfoil airfoil(M, P, T);
    wing = new Wing(&airfoil, 5.0, 1.0);

    std::vector<Nurbs::Surface*> surfaces =  wing->generate();

    if (surfaces.empty() || !surfaces[0]) {
        throw std::runtime_error("Failed to generate surfaces");
    }

    NURBSRenderer* renderer = new NURBSRenderer();
    for (Nurbs::Surface* surface : surfaces) {
         renderer->addSurface(surface);
    }

    Window window(renderer);
    window.create();
    window.render();

    // Clean up
    for (Nurbs::Surface* surface : surfaces) {
        Nurbs::freeSurface(surface);
    }

    delete wing;
    return 0;
}
