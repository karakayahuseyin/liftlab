// Copyright (C) 2025 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#include "geometry/NURBS.h"

#include <iostream>

namespace NURBS {

std::vector<double> createUniformKnotVector(int degree, int numCtrlPoints) 
{
    std::vector<double> knotVector(numCtrlPoints + degree + 1);
    for (int i = 0; i < numCtrlPoints + degree + 1; ++i) {
        knotVector[i] = static_cast<double>(i) / (numCtrlPoints + degree);
    }
    return knotVector;
}

Curve* createCurve(int degree, int numCtrlPoints, const std::vector<double>& weights) 
{
    if (weights.size() != numCtrlPoints) {
        std::cout << "Weights size must match the number of control points." << std::endl;
    }

    Curve* curve = new Curve;
    curve->degree = degree;
    curve->numCtrlPoints = numCtrlPoints;
    curve->ctrlPoints.resize(numCtrlPoints);
    curve->knotVector = createUniformKnotVector(degree, numCtrlPoints);
    curve->weights = weights;
    return curve;
}

void freeCurve(Curve* curve) 
{
    delete curve;
}

double basisFunction(int i, int degree, double u, const std::vector<double>& knotVector) 
{
    if (degree == 0) {
        return (u >= knotVector[i] && u < knotVector[i + 1]) ? 1.0 : 0.0;
    } else {
        double a = 0.0, b = 0.0;
        if (knotVector[i + degree] - knotVector[i] > 0.0) {
            a = (u - knotVector[i]) / (knotVector[i + degree] - knotVector[i]) *
                basisFunction(i, degree - 1, u, knotVector);
        }
        if (knotVector[i + degree + 1] - knotVector[i + 1] > 0.0) {
            b = (knotVector[i + degree + 1] - u) /
                (knotVector[i + degree + 1] - knotVector[i + 1]) *
                basisFunction(i + 1, degree - 1, u, knotVector);
        }
        return a + b;
    }
}

Point3D evaluateCurve(const Curve& curve, double u) 
{
    Point3D point = {0.0, 0.0, 0.0};
    double sumWeights = 0.0;

    for (int i = 0; i < curve.numCtrlPoints; ++i) {
        double Ni_u = basisFunction(i, curve.degree, u, curve.knotVector);
        double weight = curve.weights[i];

        point.x += weight * Ni_u * curve.ctrlPoints[i].x;
        point.y += weight * Ni_u * curve.ctrlPoints[i].y;
        point.z += weight * Ni_u * curve.ctrlPoints[i].z;
        sumWeights += weight * Ni_u;
    }

    point.x /= sumWeights;
    point.y /= sumWeights;
    point.z /= sumWeights;

    return point;
}

Surface* createSurface(int degreeU, int degreeV, const std::vector<Point3D>& ctrlPoints, 
                       int numCtrlPointsU, int numCtrlPointsV, const std::vector<double>& weights) 
{
    if (weights.size() != ctrlPoints.size()) {
        throw std::runtime_error("Weights size must match the number of control points.");
    }

    Surface* surface = new Surface;
    surface->degreeU = degreeU;
    surface->degreeV = degreeV;
    surface->numCtrlPointsU = numCtrlPointsU;
    surface->numCtrlPointsV = numCtrlPointsV;
    surface->ctrlPoints = ctrlPoints;
    surface->knotVectorU = createUniformKnotVector(degreeU, numCtrlPointsU);
    surface->knotVectorV = createUniformKnotVector(degreeV, numCtrlPointsV);
    surface->weights = weights;
    return surface;
}

void freeSurface(Surface* surface) 
{
    delete surface;
}

Point3D evaluateSurface(const Surface* surface, double u, double v) 
{
    Point3D point = {0.0, 0.0, 0.0};
    double sumWeights = 0.0;

    for (int i = 0; i < surface->numCtrlPointsU; ++i) {
        for (int j = 0; j < surface->numCtrlPointsV; ++j) {
            double Ni_u = basisFunction(i, surface->degreeU, u, surface->knotVectorU);
            double Nj_v = basisFunction(j, surface->degreeV, v, surface->knotVectorV);
            int index = j * surface->numCtrlPointsU + i;
            double weight = surface->weights[index];

            point.x += weight * Ni_u * Nj_v * surface->ctrlPoints[index].x;
            point.y += weight * Ni_u * Nj_v * surface->ctrlPoints[index].y;
            point.z += weight * Ni_u * Nj_v * surface->ctrlPoints[index].z;
            sumWeights += weight * Ni_u * Nj_v;
        }
    }

    point.x /= sumWeights;
    point.y /= sumWeights;
    point.z /= sumWeights;

    return point;
}

void generateMesh(const Surface* surface, std::vector<float>& vertices, const int resolutionU, const int resolutionV) 
{
    for (int i = 0; i <= resolutionU; ++i) {
        double u = i / (double)resolutionU;
        for (int j = 0; j <= resolutionV; ++j) {
            double v = j / (double)resolutionV;
            Point3D point = evaluateSurface(surface, u, v);
            vertices.push_back(point.x);
            vertices.push_back(point.y);
            vertices.push_back(point.z);
        }
    }
}

void exportObj(const Surface* surface, const char* filename)
{

}

} // namespace NURBS