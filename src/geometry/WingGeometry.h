// Copyright (C) 2025 Hüseyin Karakaya
// This file is part of the LiftLab project and is licensed under the MIT License.

#pragma once

#ifndef WING_GEOMETRY_H
#define WING_GEOMETRY_H

#include "geometry/NURBS.h"

namespace Geom {

typedef struct s_wing_sect_geom
{
    NURBS::Surface* upperSurface;
    NURBS::Surface* lowerSurface;
} WingSectGeom;

} // namespace Geom

#endif // WING_GEOMETRY_H