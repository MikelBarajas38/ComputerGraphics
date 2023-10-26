#pragma once
#include "Matrix3D.h"
#include "Vec3D.h"

class Transformation
{
public:
	static Matrix3D Translation(double Tx, double Ty, double Tz);
	static Matrix3D Scale(double Sx, double Sy, double Sz);
	static Matrix3D RotationX(double d);
	static Matrix3D RotationY(double d);
	static Matrix3D RotationZ(double d);
	static Matrix3D Identity();
	static Vec3D getCubicBezier(Vec3D p0, Vec3D p1, Vec3D p2, Vec3D p3, double t);

private:
	static double degToRad(double d);
};

