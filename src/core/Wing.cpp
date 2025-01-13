// Copyright (C) 2025 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#include "core/Wing.h"
#include "geometry/NURBS.h"

#include <vector>
#include <iostream>

#define SLICE 10

Wing::Wing(Airfoil airfoil, double span, double chord)
    : m_airfoil(airfoil), m_span(span), m_chord(chord)
{}

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
