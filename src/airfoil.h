// Copyrigt (C) 2024 Tolga Akın İnan
// This file is part of the LiftLab project and is licensed under the MIT License.

#pragma once

#ifndef AIRFOIL_GENERATOR_H
#define AIRFOIL_GENERATOR_H

#include <vector>
#include <cmath>

#include "nurbs.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define NUM_POINTS 100
#define SPLINE_DEGREE 3

class Airfoil // 4 digit
{
    
public:
    struct s_point
    {
        double X;
        double Xu;
        double Yu;
        double Xl;
        double Yl;
    };
    typedef struct s_point Point;

    Airfoil(double M, double P, double T);
    ~Airfoil() = default;

    std::vector<Point> generate();

private:
    const double a0 = 0.2969;
    const double a1 = -0.126;
    const double a2 = -0.3516;
    const double a3 = 0.2843;
    const double a4 = -0.1015;

    double M, P, T;
    std::vector<Point> airfoilData;

    std::vector<double> x, xu, yu, xl, yl;

    double camberLine(double x);
    double camberGradient(double x);
    double thicknessDistribution(double x);
};

#endif // AIRFOIL_GENERATOR_H