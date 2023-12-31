#pragma once

#include "Vec3D.h"

class Vertex
{
	public:
		Vec3D pos;
		Vec3D normal;

		Vertex(double _x, double _y, double _z) : pos(_x, _y, _z) {};
};

