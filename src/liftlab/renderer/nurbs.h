// Copyrigt (C) 2025 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#ifndef NURBS_H
#define NURBS_H

#include <vector>

namespace Nurbs {

typedef struct s_point3d { 
    double x, y, z; 
} Point3D;

typedef struct s_curve {
    int degree;
    int numCtrlPoints;
    std::vector<Point3D> ctrlPoints;
    std::vector<double> knotVector;
} Curve;

typedef struct s_surface {
    int degreeU, degreeV;
    int numCtrlPointsU, numCtrlPointsV;
    std::vector<Point3D> ctrlPoints; 
    std::vector<double> knotVectorU;
    std::vector<double> knotVectorV;
} Surface;

Curve* createCurve(int degree, int numCtrlPoints);
void freeCurve(Curve* curve);
double basisFunction(int i, int degree, double u, const std::vector<double>& knotVector);
Point3D evaluateCurve(const Curve& curve, double u);

Surface* createSurface(int degreeU, int degreeV, std::vector<Point3D> ctrlPoints, 
                       int numCtrlPointsU, int numCtrlPointsV);
void freeSurface(Surface* surface);
Point3D evaluateSurface(const Surface* surface, double u, double v);

} // namespace Nurbs

#endif // NURBS_H