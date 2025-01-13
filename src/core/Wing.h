// Copyrigt (C) 2025 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#pragma once

#ifndef WING_H
#define WING_H

#include "core/Airfoil.h"
#include "geometry/NURBS.h"

#include <vector>

class Wing {
public:
	Wing(Airfoil airfoil, double span, double chord);
	~Wing() = default;

	Airfoil airfoil() const { return m_airfoil; }
	double span() const { return m_span; }
	double chord() const { return m_chord; }
	void generate();
	
private:
	Airfoil m_airfoil;
	double m_span;
	double m_chord;

	NURBS::Surface* upperSurface;
	NURBS::Surface* lowerSurface;
};

#endif // WING_H