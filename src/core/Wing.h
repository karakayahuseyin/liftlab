// Copyrigt (C) 2025 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#pragma once

#ifndef WING_H
#define WING_H

#include "core/Airfoil.h"
#include "geometry/NURBS.h"

#include <vector>

typedef struct s_sect
{
	double span;
	double rootChord;
	double tipChord;
	double sweep;
	double dihedral;
} WingSect;

class Wing {
public:
	Wing(Airfoil airfoil, const std::vector<WingSect>& sections);
	~Wing() = default;

	Airfoil airfoil() const { return m_airfoil; }
	double span() const { return m_span; }
	double rootChord() const { return m_rootChord; }
	double tipChord() const { return m_tipChord; }
	double area() const { return m_area; }

private:
	Airfoil m_airfoil;
	std::vector<WingSect> m_sections;
	double m_span;
	double m_rootChord;
	double m_tipChord;
	double m_area;
};

#endif // WING_H