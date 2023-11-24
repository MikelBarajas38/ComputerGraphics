#pragma once
#include "Vec3D.h"
class Camera
{
	public:
		Camera();
		Camera(Vec3D _origin, Vec3D look, Vec3D _up);
		Camera(double x, double y, double z, double lookAtX, double lookAtY, double lookAtZ, double upX, double upY, double upZ);

		Vec3D& getPos() { return this->pos; };
		Vec3D getDirection();

		float getX() { return this->pos.x; };
		float getY() { return this->pos.y; };
		float getZ() { return this->pos.z; };
		float getLookAtX() { return this->lookAt.x; };
		float getLookAtY() { return this->lookAt.y; };
		float getLookAtZ() { return this->lookAt.z; };
		float getUpX() { return this->up.x; };
		float getUpY() { return this->up.y; };
		float getUpZ() { return this->up.z; };

	private:
		Vec3D pos;
		Vec3D lookAt;
		Vec3D up;
};

