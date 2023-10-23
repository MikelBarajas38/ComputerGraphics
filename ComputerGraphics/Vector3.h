#pragma once

template<typename T>
class Vector3
{

	public:
		T x;
		T y;
		T z;
		T w;

		Vector3() : x(0), y(0), z(0), w(1) {};
		Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z), w(1){};

};

typedef Vector3<double> Vec3D;


