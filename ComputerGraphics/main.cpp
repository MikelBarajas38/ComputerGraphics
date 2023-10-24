#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "Object3D.h"

std::vector<Object3D> objectList;

int lastFrameTime = 0;
int currentFrameTime = 0;
int frameCount = 0;
int currentTime, previousTime;

void display(void)
{
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	currentFrameTime = glutGet(GLUT_ELAPSED_TIME);
	currentTime = currentFrameTime;
	double deltaTime = (currentFrameTime - lastFrameTime);
	double deltaFrame = currentTime - previousTime;

	frameCount++;

	// Calculate FPS every second
	if (deltaFrame > 1000) {
		int fps = frameCount * 1000 / deltaTime;
		std::cout << "FPS: " << fps << std::endl;

		// Reset frame count and time
		frameCount = 0;
		previousTime = currentTime;
	}

	lastFrameTime = currentFrameTime;


	glBegin(GL_TRIANGLES);
	for (Object3D& object : objectList) {
		object.draw(deltaTime);
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
	//gluLookAt(0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0); //top down view

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
	std::string filename = "C:\\Users\\mikel\\OneDrive\\Documents\\Star.obj";
	std::string filename1 = "C:\\Users\\mikel\\OneDrive\\Documents\\dode.obj";
	std::string filename2 = "C:\\Users\\mikel\\OneDrive\\Documents\\soda.obj";
	std::string filename3 = "C:\\Users\\mikel\\OneDrive\\Documents\\FishBone.obj";
	std::string filename4 = "C:\\Users\\mikel\\OneDrive\\Escritorio\\computer graphics\\v3\\untitled.obj";

	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			Object3D origin(filename4);
			origin.translate((i - 10) * 2, 0, (j - 10)*2);
			origin.setControlPoint();
			origin.scale(.3);
			origin.setControlPoint();
			objectList.push_back(origin);
		}
	}

	//Object3D object1(filename);
	//object1.print();
	//object1.rotateY(0);
	//object1.translate(2, 0, 0);
	//object1.setMidPoint();
	//objectList.push_back(object1);

	//Object3D object2(filename2);
	//object2.print();
	//object2.translate(-2, 0, 0);
	//objectList.push_back(object2);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Segunda Entrega");
	init();
	glutDisplayFunc(display);
	//glutPostRedisplay();
	glutIdleFunc(display);
	glutMainLoop();

	return 0;   /* ISO C requires main to return int. */
}
