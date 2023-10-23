#pragma once

#include <vector>
#include "Vector3.h"

class Matrix3D
{
	private:
		std::vector<std::vector<double>> data;

	public:
		Matrix3D(int rows, int cols) : data(rows, std::vector<double>(cols, 0.0)) {}
		Matrix3D(std::initializer_list<std::vector<double>> values) : data(values) {}


		double* operator[](int i);
		Matrix3D operator*(const Matrix3D& other);
		Vec3D operator*(const Vec3D& v);

		void print();
};

