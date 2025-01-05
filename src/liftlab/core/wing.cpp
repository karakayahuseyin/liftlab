// Copyright (C) 2025 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#include "liftlab/core/wing.h"
#include "liftlab/renderer/nurbs.h"

void writeSurfaceToAscii(const std::string& filename, const Nurbs::Surface* surface) 
{
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw std::runtime_error("Unable to open file for writing: " + filename);
    }

    // Knot vectors, control points, and weights
    const std::vector<double>& knotVectorU = surface->knotVectorU;
    const std::vector<double>& knotVectorV = surface->knotVectorV;
    const std::vector<Nurbs::Point3D>& controlPoints = surface->ctrlPoints;
    const std::vector<double>& weights = surface->weights;

    int degreeU = surface->degreeU;
    int degreeV = surface->degreeV;
    int numControlPointsU = surface->numCtrlPointsU;
    int numControlPointsV = surface->numCtrlPointsV;

    // Writing Knot Vector U
    outFile << "b-spline dugumleri dizi eleman adedi (U)\n";
    outFile << knotVectorU.size() << "\n";
    outFile << "b-spline dugum dizisi (U)\n";
    for (size_t i = 0; i < knotVectorU.size(); ++i) {
        outFile << knotVectorU[i];
        if (i < knotVectorU.size() - 1) {
            outFile << ",";
        }
    }
    outFile << "\n";

    // Writing Knot Vector V
    outFile << "b-spline dugumleri dizi eleman adedi (V)\n";
    outFile << knotVectorV.size() << "\n";
    outFile << "b-spline dugum dizisi (V)\n";
    for (size_t i = 0; i < knotVectorV.size(); ++i) {
        outFile << knotVectorV[i];
        if (i < knotVectorV.size() - 1) {
            outFile << ",";
        }
    }
    outFile << "\n";

    // Writing Degrees
    outFile << "b-spline derecesi (U)\n";
    outFile << degreeU << "\n";
    outFile << "b-spline derecesi (V)\n";
    outFile << degreeV << "\n";

    // Writing Control Points Count
    outFile << "b-spline kontrol noktalari adedi\n";
    outFile << numControlPointsU * numControlPointsV << "\n";

    // Writing Control Points
    outFile << "b-spline kontrol noktalari\n";
    for (size_t i = 0; i < controlPoints.size(); ++i) {
        outFile << controlPoints[i].x << ";" << controlPoints[i].y << ";" << controlPoints[i].z;
        if (i < controlPoints.size() - 1) {
            outFile << ";";
        }
    }
    outFile << "\n";

    // Writing Weights
    outFile << "agirlik vektoru\n";
    for (size_t i = 0; i < weights.size(); ++i) {
        outFile << weights[i];
        if (i < weights.size() - 1) {
            outFile << ",";
        }
    }
    outFile << "\n";

    outFile.close();
    std::cout << "Surface written to ASCII file: " << filename << std::endl;
}

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
    std::vector<double> weights; // Add weights

    // double z_step = m_span / SLICE;
    // double sweep_step = (m_chord * 0.2) / SLICE;

    for (int j = 0; j < 2; ++j) {
        for (int i = 0; i < airfoilPoints.size(); ++i) {
            upperCtrlPoints.push_back({ airfoilPoints[i].Xu, airfoilPoints[i].Yu, m_span * j });
            lowerCtrlPoints.push_back({ airfoilPoints[i].Xl, airfoilPoints[i].Yl, m_span * j });
            weights.push_back(1.0); // Uniform weights
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

    Nurbs::Surface* upperSurface = Nurbs::createSurface(3, 3, upperCtrlPoints, numCtrlPointsU, numCtrlPointsV, weights);
    Nurbs::Surface* lowerSurface = Nurbs::createSurface(3, 3, lowerCtrlPoints, numCtrlPointsU, numCtrlPointsV, weights);

    writeSurfaceToAscii("upper_surface.txt", upperSurface);
    writeSurfaceToAscii("lower_surface.txt", lowerSurface);
    
    std::vector<Nurbs::Surface*> surfaces = { upperSurface, lowerSurface };

    std::cout << "Wing generated" << std::endl;
    return surfaces;
}
