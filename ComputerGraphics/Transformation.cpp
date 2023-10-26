#include "Transformation.h"

#define M_PI 3.14159265358979323846

Matrix3D Transformation::Translation(double Tx, double Ty, double Tz)
{
    return Matrix3D({{1,0,0,Tx}, 
                     {0,1,0,Ty}, 
                     {0,0,1,Tz}, 
                     {0,0,0,1} });
}

Matrix3D Transformation::Scale(double Sx, double Sy, double Sz)
{
    return Matrix3D({ {Sx,0,0,0}, 
                      {0,Sy,0,0}, 
                      {0,0,Sz,0}, 
                      {0,0,0,1} });
}

Matrix3D Transformation::RotationX(double d)
{
    d = degToRad(d);
    double cosD = cos(d);
    double sinD = sin(d);

    return Matrix3D({ {1, 0, 0, 0},
                      {0, cosD, -sinD, 0},
                      {0, sinD, cosD, 0},
                      {0, 0, 0, 1} });
}

Matrix3D Transformation::RotationY(double d)
{
    d = degToRad(d);
    double cosD = cos(d);
    double sinD = sin(d);

    return Matrix3D({ {cosD, 0, sinD, 0},
                      {0, 1, 0, 0},
                      {-sinD, 0, cosD, 0},
                      {0, 0, 0, 1} });
}

Matrix3D Transformation::RotationZ(double d)
{
    d = degToRad(d);
    double cosD = cos(d);
    double sinD = sin(d);

    return Matrix3D({ {cosD, -sinD, 0, 0},
                      {sinD, cosD, 0, 0},
                      {0, 0, 1, 0},
                      {0, 0, 0, 1} });
}

Matrix3D Transformation::Identity()
{
    return Matrix3D({ {1,0,0,0},
                      {0,1,0,0},
                      {0,0,1,0},
                      {0,0,0,1} });
}

Vec3D Transformation::getCubicBezier(Vec3D p0, Vec3D p1, Vec3D p2, Vec3D p3, double t)
{
    double nt = 1 - t;

    double x = nt * nt * nt * p0.x + 3 * t * nt * nt * p1.x + 3 * t * t * nt * p2.x + t * t * t * p3.x;
    double y = nt * nt * nt * p0.y + 3 * t * nt * nt * p1.y + 3 * t * t * nt * p2.y + t * t * t * p3.y;
    double z = nt * nt * nt * p0.z + 3 * t * nt * nt * p1.z + 3 * t * t * nt * p2.z + t * t * t * p3.z;

    return Vec3D(x, y, z);
}

double Transformation::degToRad(double d)
{
    return d * M_PI / 180.0;
}

