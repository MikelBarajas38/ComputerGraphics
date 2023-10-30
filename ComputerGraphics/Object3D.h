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
		std::string name;
		//AnimationManager animationManager;

	public:
		Object3D(std::string meshFile);
		void setColor(double r, double g, double b);
		void draw();
		void print();
		void transform(Matrix3D M);
		void translate(double x, double y, double z);
		void translateOrigin();
		void traslateToControlPoint();
		void scale(double s);
		void rotateX(double d);
		void rotateY(double d);
		void rotateZ(double d);
		void clearTransformations();
		void setControlPoint();

		std::string getName();
		void setName(std::string _name);
		// void addAnimation();


};

