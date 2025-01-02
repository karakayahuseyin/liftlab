// Copyrigt (C) 2025 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#pragma once

#ifndef WING_H
#define WING_H

#include <vector>
#include "liftlab/core/airfoil.h"
#include "liftlab/renderer/nurbs.h"

class Wing {
public:
	Wing(Airfoil airfoil, double span, double chord);
	~Wing() = default;
	
	std::vector<Nurbs::Surface*> generate();
private:
	Airfoil m_airfoil;
	double m_span;
	double m_chord;
};

#endif