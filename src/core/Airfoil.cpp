﻿// Copyrigt (C) 2024 Tolga Akın İnan
// This file is part of the LiftLab project and is licensed under the MIT License.

#include <iostream>
#include <cmath>

#include "core/Airfoil.h"

const double a0 = 0.2969;
const double a1 = -0.126;
const double a2 = -0.3516;
const double a3 = 0.2843;
const double a4 = -0.1015;

Airfoil::Airfoil(double M, double P, double T)
    : M(M / 100.0), P(P / 10.0), T(T / 100.0),
    x(NUM_POINTS), xu(NUM_POINTS), yu(NUM_POINTS), xl(NUM_POINTS), yl(NUM_POINTS) {
}

Airfoil::Airfoil(int airfoilNum)
    : M(airfoilNum / 10000.0), P(((airfoilNum / 100) % 10) / 10), T((airfoilNum % 100) / 100),
    x(NUM_POINTS), xu(NUM_POINTS), yu(NUM_POINTS), xl(NUM_POINTS), yl(NUM_POINTS) {
}

double Airfoil::camberLine(double x)
{
    if (x <= P) {
        return (M / (P * P)) * (2 * P * x - x * x);
    }
    else {
        return (M / ((1 - P) * (1 - P))) * ((1 - 2 * P) + 2 * P * x - x * x);
    }
}

double Airfoil::camberGradient(double x)
{
  	if (x <= P) {
        return (2 * M / (P * P)) * (P - x);
    }
    else {
        return (2 * M / ((1 - P) * (1 - P))) * (P - x);
    }
}

double Airfoil::thicknessDistribution(double x) {
    return 5 * T * (a0 * std::sqrt(x) + a1 * x + a2 * x * x + a3 * x * x * x + a4 * x * x * x * x);
}

void Airfoil::generate()
{
    // Generate the airfoil points
    for (int i = 0; i < NUM_POINTS; ++i) {
        Point point;

        double beta = M_PI * i / (NUM_POINTS - 1);
        point.X = (1 - std::cos(beta)) / 2;

        double yc = camberLine(point.X);
        double dyc_dx = camberGradient(point.X);
        double theta = std::atan(dyc_dx);
        double yt = thicknessDistribution(point.X);

        point.Xu = point.X - yt * std::sin(theta);
        point.Yu = yc + yt * std::cos(theta);
        point.Xl = point.X + yt * std::sin(theta);
        point.Yl = yc - yt * std::cos(theta);

        airfoilPoints.push_back(point);
    } 

    if (airfoilPoints.size() < NUM_POINTS) {
        std::cerr << "Error: airfoilPoints vector must have at least" 
                        << NUM_POINTS << "elements!" << std::endl;
        airfoilPoints.clear();
        return;
    }

    // Set the leading edge and trailing edge points
    this->airfoilPoints[0] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
    this->airfoilPoints[99] = { 1.0, 1.0, 0.0, 1.0, 0.0 };
}