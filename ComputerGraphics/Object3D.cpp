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
	translateOrigin();
}

void Object3D::draw()
{
	for (Face& face : model.getFaceList()) {
		glColor3fv(face.getColor());
		//glColor3f(randomFloat(), randomFloat(), randomFloat());
		Vec3D v1 = MM * model.getVertexList()[face.getVertexIndexList()[0]].pos;
		Vec3D v2 = MM * model.getVertexList()[face.getVertexIndexList()[1]].pos;
		Vec3D v3 = MM * model.getVertexList()[face.getVertexIndexList()[2]].pos;
		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		glVertex3f(v3.x, v3.y, v3.z);
	}
}

void Object3D::print()
{
	model.printObj();
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
