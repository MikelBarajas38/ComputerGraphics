#pragma once
#include "Vec3D.h"
class DirectionalLight
{
	public:
		DirectionalLight(Vec3D _origin, Vec3D look);
		DirectionalLight(Vec3D _origin, Vec3D look, double r, double g, double b);
		DirectionalLight(Vec3D _origin, Vec3D look, double r, double g, double b, double _specular);

		float* getIntensity() { return this->intensity; }
		Vec3D& getDirection() { return this->dir; }
		float getSpecularFactor() { return this->specularFactor; }
		bool isActive() { return this->active; }
		void turnOn();
		void turnOff();
		void change();

	private:
		Vec3D origin;
		Vec3D dir;
		float intensity[4];
		float specularFactor;
		bool active;

};

