// Copyright (C) 2025 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#include "core/Wing.h"
#include "geometry/NURBS.h"

#include <vector>
#include <iostream>

Wing::Wing(Airfoil airfoil, const std::vector<WingSect>& sections)
    : m_airfoil(airfoil), m_sections(sections)
{
    m_rootChord = m_sections[0].rootChord;
    m_tipChord = m_sections[m_sections.size() - 1].tipChord;

    for (int i = 0; i < m_sections.size(); ++i) {
        m_span += m_sections[i].span;
        m_area += (m_sections[i].rootChord + m_sections[i].tipChord) * m_sections[i].span / 2;
    }
}

// std::vector<NURBS::Surface*> Wing::generate() 
// {
//     std::vector<Airfoil::Point> airfoilPoints = m_airfoil.generate();

//     std::vector<NURBS::Point3D> upperCtrlPoints;
//     std::vector<NURBS::Point3D> lowerCtrlPoints;
//     std::vector<double> weights; // Add weights

//     for (int j = 0; j < 2; ++j) {
//         for (int i = 0; i < airfoilPoints.size(); ++i) {
//             upperCtrlPoints.push_back({ airfoilPoints[i].Xu, airfoilPoints[i].Yu, m_span * j });
//             lowerCtrlPoints.push_back({ airfoilPoints[i].Xl, airfoilPoints[i].Yl, m_span * j });
//             weights.push_back(1.0); // Uniform weights
//         }
//     }

//     int numCtrlPointsU = airfoilPoints.size();
//     int numCtrlPointsV = 2;

//     if (upperCtrlPoints.size() != numCtrlPointsU * numCtrlPointsV) {
//         throw std::runtime_error("Upper control points size mismatch");
//     }
//     if (lowerCtrlPoints.size() != numCtrlPointsU * numCtrlPointsV) {
//         throw std::runtime_error("Lower control points size mismatch");
//     }

//     NURBS::Surface* upperSurface = NURBS::createSurface(3, 3, upperCtrlPoints, numCtrlPointsU, numCtrlPointsV, weights);
//     NURBS::Surface* lowerSurface = NURBS::createSurface(3, 3, lowerCtrlPoints, numCtrlPointsU, numCtrlPointsV, weights);
    
//     std::vector<NURBS::Surface*> surfaces = { upperSurface, lowerSurface };

//     std::cout << "Wing generated" << std::endl;
//     return surfaces;
// }
