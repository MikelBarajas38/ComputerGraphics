#pragma once

#include <GL/freeglut.h>

#include "Mesh.h"
#include "Matrix3D.h"

class Object3D
{
	private:
		Mesh model;
		Matrix3D MM;
		Vec3D controlPoint;
		//AnimationManager animationManager;

	public:
		Object3D(std::string meshFile);
		void draw(double deltaTime);
		void print();
		void translate(double x, double y, double z);
		void translateOrigin();
		void scale(double s);
		void rotateX(double d);
		void rotateY(double d);
		void rotateZ(double d);
		void clearTransformations();
		void setControlPoint();
		// void addAnimation();


};

