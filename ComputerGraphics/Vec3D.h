#pragma once

#include<vector>

class Vec3D
{

	public:
		double x;
		double y;
		double z;
		double w;

		Vec3D() : x(0), y(0), z(0), w(1) {};
		Vec3D(double _x, double _y, double _z) : x(_x), y(_y), z(_z), w(1.0) {};

		Vec3D operator+(const Vec3D& v);
		Vec3D operator-(const Vec3D& v);

		void print();

		double dot(const Vec3D& v);
		Vec3D cross(const Vec3D& v);
		Vec3D norm();

};



