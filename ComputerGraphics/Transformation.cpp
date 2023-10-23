#include "Transformation.h"

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
    double cosD = cos(d);
    double sinD = sin(d);

    return Matrix3D({ {1, 0, 0, 0},
                      {0, cosD, -sinD, 0},
                      {0, sinD, cosD, 0},
                      {0, 0, 0, 1} });
}

Matrix3D Transformation::RotationY(double d)
{
    double cosD = cos(d);
    double sinD = sin(d);

    return Matrix3D({ {cosD, 0, sinD, 0},
                      {0, 1, 0, 0},
                      {-sinD, 0, cosD, 0},
                      {0, 0, 0, 1} });
}

Matrix3D Transformation::RotationZ(double d)
{
    double cosD = cos(d);
    double sinD = sin(d);

    return Matrix3D({ {cosD, -sinD, 0, 0},
                      {sinD, cosD, 0, 0},
                      {0, 0, 1, 0},
                      {0, 0, 0, 1} });
}

