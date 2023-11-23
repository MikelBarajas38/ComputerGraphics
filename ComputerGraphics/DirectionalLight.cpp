#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Vec3D _origin, Vec3D look)
{
	origin = _origin;
	dir = (origin - look).norm();
	intensity[0] = intensity[1] = intensity[2] = 1;
	intensity[3] = 0.0;
}

DirectionalLight::DirectionalLight(Vec3D _origin, Vec3D look, double r, double g, double b)
{
	origin = _origin;
	dir = (origin - look).norm();
	intensity[0] = r;
	intensity[1] = g;
	intensity[2] = b;
	intensity[3] = 0.0;
}


