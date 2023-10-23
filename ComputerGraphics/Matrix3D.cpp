#include "Matrix3D.h"
#include <iostream>

double* Matrix3D::operator[](int i)
{
    return data[i].data();
}

Matrix3D Matrix3D::operator*(const Matrix3D& other)
{
    Matrix3D result(data.size(), other.data[0].size());
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < other.data[0].size(); ++j) {
            for (int k = 0; k < other.data.size(); ++k) {
                result[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

Vec3D Matrix3D::operator*(const Vec3D& v) 
{
    Vec3D result;
    result.x = data[0][0] * v.x + data[0][1] * v.y + data[0][2] * v.z + data[0][3] * v.w;
    result.y = data[1][0] * v.x + data[1][1] * v.y + data[1][2] * v.z + data[1][3] * v.w;
    result.z = data[2][0] * v.x + data[2][1] * v.y + data[2][2] * v.z + data[2][3] * v.w;
    result.w = data[3][0] * v.x + data[3][1] * v.y + data[3][2] * v.z + data[3][3] * v.w;
    return result;
}

void Matrix3D::print()
{
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[0].size(); ++j) {
            std::cout << data[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

