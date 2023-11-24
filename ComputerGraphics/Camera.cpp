#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(Vec3D _pos, Vec3D _lookAt, Vec3D _up)
{
    pos = _pos;
    lookAt = _lookAt;
    up = _up;
}

Camera::Camera(double x, double y, double z, double lookAtX, double lookAtY, double lookAtZ, double upX, double upY, double upZ)
{
    pos = Vec3D(x, y, z);
    lookAt = Vec3D(lookAtX, lookAtY, lookAtZ);
    up = Vec3D(upX, upY, upZ);
}

Vec3D Camera::getDirection()
{
    return (lookAt - pos).norm();
}
