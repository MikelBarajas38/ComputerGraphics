#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "Mesh.h"
#include "ObjParser.h"
#include "Matrix3D.h"
#include "Vec3D.h"

std::vector<Mesh> modelList;

void display(void)
{
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	for (Mesh& model : modelList) {
		for (Face& face : model.getFaceList()) {
			glColor3fv(face.getColor());
			//glColor3f(randomFloat(), randomFloat(), randomFloat());
			Vertex v1 = model.getVertexList()[face.getVertexIndexList()[0]];
			Vertex v2 = model.getVertexList()[face.getVertexIndexList()[1]];
			Vertex v3 = model.getVertexList()[face.getVertexIndexList()[2]];
			glVertex3f(v1.x, v1.y, v1.z);
			glVertex3f(v2.x, v2.y, v2.z);
			glVertex3f(v3.x, v3.y, v3.z);
		}
	}
	glEnd();

	glutSwapBuffers();
	glFlush();
}

void init(void)
{
	/*  select clearing (background) color       */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/*  initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	//gluOrtho2D(0.0, 1.0, 0.0, 1.0);

	gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(2.0, 10.0, 10.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0); //normal view
	//gluLookAt(0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0); //top down view

	glEnable(GL_DEPTH_TEST);

}

/*
 *  Declare initial window size, position, and display mode
 *  (single buffer and RGBA).  Open window with "hello"
 *  in its title bar.  Call initialization routines.
 *  Register callback function to display graphics.
 *  Enter main loop and process events.
 */
int main(int argc, char** argv)
{
	srand(time(0));

	Vec3D vectorTest(3.0,3.0,3.0);

	Matrix3D matrixTest({{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}});
	matrixTest.print();

	Vec3D newVec = matrixTest * vectorTest;
	std::cout << newVec.x << ' ' << newVec.y << ' ' << newVec.z << '\n';

	Matrix3D matrix2({ {1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4} });
	matrix2.print();

	Matrix3D res = matrix2 * matrixTest;
	res.print();

	Matrix3D matrix3({ {1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1} });
	(matrix3 * matrix3).print();

	getchar();

	std::string filename = "C:\\Users\\mikel\\OneDrive\\Documents\\Star.obj";
	//std::string filename = "C:\\Users\\mikel\\OneDrive\\Documents\\dode.obj";
	//std::string filename = "C:\\Users\\mikel\\OneDrive\\Documents\\soda.obj";
	std::string filename2 = "C:\\Users\\mikel\\OneDrive\\Documents\\FishBone.obj";
	//std::string filename = "C:\\Users\\mikel\\OneDrive\\Escritorio\\computer graphics\\v3\\untitled.obj";

	Mesh model1 = ObjParser::parse(filename);
	model1.printObj();
	model1.assignRandomColor();
	modelList.push_back(model1);

	Mesh model2 = ObjParser::parse(filename2);
	model2.printObj();
	model2.assignRandomColor();
	modelList.push_back(model2);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Primera Entrega");
	init();
	glutDisplayFunc(display);
	//glutPostRedisplay();
	glutIdleFunc(display);
	glutMainLoop();

	return 0;   /* ISO C requires main to return int. */
}
