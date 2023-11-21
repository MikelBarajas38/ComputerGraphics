#include "Object3D.h"
#include "ObjParser.h"
#include "Transformation.h"
#include <iostream>

Object3D::Object3D(std::string meshFile)
{
	model = ObjParser::parse(meshFile);
	model.assignRandomColor();
	controlPoint = model.getMidPoint();
	MM = Transformation::Identity();
	name = model.getName();
	//translateOrigin();
	model.init();
}

void Object3D::print()
{
	model.printObj();
}

void Object3D::setColor(int r, int g, int b)
{

	model.setColor((double) r / 255, (double) g / 255, (double) b/ 255);
}

void Object3D::transform(Matrix3D M)
{
	MM = M;
}

void Object3D::translateOrigin()
{
	Matrix3D T = Transformation::Translation(-controlPoint.x, -controlPoint.y, -controlPoint.z);
	MM = T * MM;
}

void Object3D::scale(double s)
{
	Matrix3D S = Transformation::Scale(s, s, s);
	MM = S * MM;
}

void Object3D::traslateToControlPoint()
{
	Matrix3D T = Transformation::Translation(controlPoint.x, controlPoint.y, controlPoint.z);
	MM = T * MM;
}

void Object3D::clearTransformations()
{
	MM = Transformation::Identity();
}

void Object3D::rotateX(double d)
{
	Matrix3D R = Transformation::RotationX(d);

	MM = R * MM;
}

std::string Object3D::getName()
{
	return name;
}

void Object3D::setName(std::string _name)
{
	name = _name;
}

Mesh Object3D::getMesh()
{
	return model;
}

Matrix3D Object3D::getModelMatrix()
{
	return MM;
}

void Object3D::setControlPoint()
{
	controlPoint = MM * controlPoint;
}

void Object3D::rotateY(double d)
{
	Matrix3D R = Transformation::RotationY(d);

	MM = R * MM;
}

void Object3D::rotateZ(double d)
{
	Matrix3D R = Transformation::RotationZ(d);

	MM = R * MM;
}

void Object3D::translate(double x, double y, double z)
{
	Matrix3D T = Transformation::Translation(x, y, z);
	MM = T * MM;
}
