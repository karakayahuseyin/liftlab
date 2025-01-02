// Copyrigt (C) 2025 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#include <iostream>

#include "liftlab/core/wing.h"
#include "liftlab/renderer/nurbs.h"

#define SLICE 10

Wing::Wing(Airfoil airfoil, double span, double chord)
	: m_airfoil(airfoil), m_span(span), m_chord(chord)
{
}

std::vector<Nurbs::Surface*> Wing::generate() 
{
    std::vector<Airfoil::Point> airfoilPoints = m_airfoil.generate();
    
    std::vector<Nurbs::Point3D> upperCtrlPoints;
    std::vector<Nurbs::Point3D> lowerCtrlPoints;

    // double z_step = m_span / SLICE;
    // double sweep_step = (m_chord * 0.2) / SLICE;

    for (int j = 0; j < 2; ++j) {
        for (int i = 0; i < airfoilPoints.size(); ++i) {
            upperCtrlPoints.push_back({ airfoilPoints[i].Xu, airfoilPoints[i].Yu, m_span * j });
            lowerCtrlPoints.push_back({ airfoilPoints[i].Xl, airfoilPoints[i].Yl, m_span * j });
        }
    }

    int numCtrlPointsU = airfoilPoints.size();
    int numCtrlPointsV = 2;

    if (upperCtrlPoints.size() != numCtrlPointsU * numCtrlPointsV) {
        throw std::runtime_error("Upper control points size mismatch");
    }
    if (lowerCtrlPoints.size() != numCtrlPointsU * numCtrlPointsV) {
        throw std::runtime_error("Lower control points size mismatch");
    }

    Nurbs::Surface* upperSurface = Nurbs::createSurface(3, 3, upperCtrlPoints, numCtrlPointsU, numCtrlPointsV);
    Nurbs::Surface* lowerSurface = Nurbs::createSurface(3, 3, lowerCtrlPoints, numCtrlPointsU, numCtrlPointsV);

    std::vector<Nurbs::Surface*> surfaces = { upperSurface, lowerSurface };

    std::cout << "Wing generated" << std::endl;
    return surfaces;
}
