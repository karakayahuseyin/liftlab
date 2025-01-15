// Copyrigt (C) 2024 Tolga Akın İnan
// This file is part of the LiftLab project and is licensed under the MIT License.

#pragma once

#ifndef AIRFOIL_GENERATOR_H
#define AIRFOIL_GENERATOR_H

#include <vector>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define NUM_POINTS 100

class Airfoil {
public:
    typedef struct s_point
    {
        double X;
        double Xu;
        double Yu;
        double Xl;
        double Yl;
    } Point;

    Airfoil(double M, double P, double T);
    Airfoil(int airfoilNum);
    ~Airfoil() = default;

    void generate();
    std::vector<Point> getAirfoilPoints() const { return airfoilPoints; }

private:
    double M, P, T;
    std::vector<double> x, xu, yu, xl, yl;
    std::vector<Airfoil::Point> airfoilPoints;

    double camberLine(double x);
    double camberGradient(double x);
    double thicknessDistribution(double x);
};

#endif // AIRFOIL_GENERATOR_H