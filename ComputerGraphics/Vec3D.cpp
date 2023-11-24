#include "Vec3D.h"
#include <iostream>

Vec3D Vec3D::operator+(const Vec3D& v)
{
	return Vec3D(x + v.x, y + v.y, z + v.z);
}

Vec3D Vec3D::operator-(const Vec3D& v)
{
	return Vec3D(x - v.x, y - v.y, z - v.z);
}

Vec3D Vec3D::operator*(const double& d)
{
	return Vec3D(x * d, y * d, z * d);
}

void Vec3D::print()
{
	std::cout << "(" << x << ", " << y << ", " << z << ")\n";
}

double Vec3D::dot(const Vec3D& v)
{
	return x * v.x + y * v.y + z * v.z;
}

Vec3D Vec3D::cross(const Vec3D& v)
{
	return Vec3D(y * v.z - z * v.y,
				 z * v.x - x * v.z,
				 x * v.y - y * v.x);
}

Vec3D Vec3D::norm()
{
    double magnitude = std::sqrt(x * x + y * y + z * z);
	return (magnitude > 0.0) ? Vec3D(x / magnitude, y / magnitude, z / magnitude) : *this;
}
