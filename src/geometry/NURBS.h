// Copyright (C) 2025 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#ifndef NURBS_H
#define NURBS_H

#include "Geometry.h"
#include <vector>

namespace Geom {
namespace NURBS {

typedef struct s_curve {
    int degree;
    int numCtrlPoints;
    std::vector<Point3D> ctrlPoints;
    std::vector<double> knotVector;
    std::vector<double> weights; // Added weights
} Curve;

typedef struct s_surface {
    int degreeU, degreeV;
    int numCtrlPointsU, numCtrlPointsV;
    std::vector<Point3D> ctrlPoints; 
    std::vector<double> knotVectorU;
    std::vector<double> knotVectorV;
    std::vector<double> weights; // Added weights
} Surface;

Curve* createCurve(int degree, int numCtrlPoints, const std::vector<double>& weights);
void freeCurve(Curve* curve);
double basisFunction(int i, int degree, double u, const std::vector<double>& knotVector);
Point3D evaluateCurve(const Curve& curve, double u);

Surface* createSurface(int degreeU, int degreeV, const std::vector<Point3D>& ctrlPoints, 
                       int numCtrlPointsU, int numCtrlPointsV, const std::vector<double>& weights);
void freeSurface(Surface* surface);
Point3D evaluateSurface(const Surface* surface, double u, double v);

void exportSurface_STEP(const Surface* surface, const char* filename);

} // namespace NURBS
} // namespace Geom

#endif // NURBS_H
