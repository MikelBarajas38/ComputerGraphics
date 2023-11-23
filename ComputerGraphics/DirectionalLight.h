#pragma once
#include "Vec3D.h"
class DirectionalLight
{
	public:
		DirectionalLight(Vec3D _origin, Vec3D look);
		DirectionalLight(Vec3D _origin, Vec3D look, double r, double g, double b);

		float* getIntensity() { return this->intensity; }
		Vec3D& getDirection() { return this->dir; }

	private:
		Vec3D origin;
		Vec3D dir;
		float intensity[4];

};

