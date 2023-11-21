#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "Object3D.h"
#include "Transformation.h"

std::vector<Object3D> objectList;

std::vector<std::vector<Vec3D>> path;
int current = 0;

std::vector<Vec3D> allPos;
int posi = 0;

int lastFrameTime = 0;
int currentFrameTime = 0;
double deltaTime;

int frameCount = 0;
int lastFrame = 0;
int currentFrame = 0;
double deltaFrame;

double temp = 0.1;
double t = 0;
double offset = 0.001;

//realtime calculation of new position

void animation1(Object3D &object)
{
	Vec3D newPos = Transformation::getCubicBezier(Vec3D(0, 0, 0), Vec3D(1.5, 0, 2), Vec3D(3, 0, -2), Vec3D(4.5, 0, 0), t);

	Matrix3D M = Transformation::Translation(newPos.x, newPos.y, newPos.z) *
				 Transformation::RotationY(temp) *
				 Transformation::Scale(0.4, 0.4, 0.4);

	object.transform(M);

	if (t < 0)
	{
		t = 0;
		offset *= -1;
	}
	else if (t > 1)
	{
		t = 1;
		offset *= -1;
	}

	t += offset;

	temp += 0.1;
}

void animation2(Object3D& object)
{
	Vec3D newPos = Transformation::getCubicBezier(path[current][0], path[current][1], path[current][2], path[current][3], t);

	Matrix3D M = Transformation::Translation(newPos.x, newPos.y, newPos.z) *
				 Transformation::RotationX(270) *
				 Transformation::RotationY(temp) *
				 Transformation::Scale(0.4, 0.4, 0.4);

	object.transform(M);

	if (t > 1)
	{
		t = 0;
		current = (current + 1)%4;
	}
	
	t += offset;

	temp += 0.8;

}

void animation3(Object3D& object, double dt)
{
	int dc = 0;
	if (t < dt) dc = -1;

	Vec3D newPos = Transformation::getCubicBezier(path[current + dc][0], path[current + dc][1], path[current + dc][2], path[current + dc][3], t + dt);

	Matrix3D M = Transformation::Translation(newPos.x, newPos.y, newPos.z) *
				 Transformation::RotationX(270) *
				 Transformation::RotationY(360 - temp) *
				 Transformation::Scale(0.2, 0.2, 0.2);

	object.transform(M);
}

//precomputed positions

std::vector<Vec3D> generatePositions(double dt)
{
	std::vector<Vec3D> positions;
	for (auto& v : path) {
		for (double j = 0; j <= 1; j += dt) {
			Vec3D newPos = Transformation::getCubicBezier(v[0], v[1], v[2], v[3], j);
			positions.push_back(newPos);
		}
	}
	return positions;
}

void animationp1(Object3D& object)
{
	if (posi >= allPos.size()) posi = 0;

	Matrix3D M = Transformation::Translation(allPos[posi].x, allPos[posi].y, allPos[posi].z) *
				 Transformation::RotationX(270) *
				 Transformation::RotationY(temp) *
				 Transformation::Scale(0.4, 0.4, 0.4);

	object.transform(M);

	posi++;

	temp += 0.1;
}

void animationp2(Object3D& object, int di)
{
	int ni = posi - di;
	if (ni < 0) ni = allPos.size() + ni;

	Matrix3D M = Transformation::Translation(allPos[ni].x, allPos[ni].y, allPos[ni].z) *
				 Transformation::RotationX(270) *
				 Transformation::RotationY(360 - temp) *
				 Transformation::Scale(0.2, 0.2, 0.2);

	object.transform(M);
}

void display(void)
{
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	currentFrameTime = glutGet(GLUT_ELAPSED_TIME);
	currentFrame = currentFrameTime;

	deltaTime = currentFrameTime - lastFrameTime; //for future animations maybe?
	deltaFrame = currentFrame - lastFrame;

	lastFrameTime = currentFrameTime;

	frameCount++;

	glBegin(GL_TRIANGLES);
	for (Object3D& object : objectList) {

		if (object.getName() == "test") {
			animationp1(object);
		}
		else if (object.getName() == "test2") {
			animationp2(object, 200);
		}
		else if (object.getName() == "test3") {
			animationp2(object, 400);
		}

		Mesh model = object.getMesh();
		Matrix3D MM = object.getModelMatrix();

		for (Face& face : model.getFaceList()) {
			glColor3fv(face.getColor());
			Vec3D v1 = MM * model.getVertexList()[face.getVertexIndexList()[0]].pos;
			Vec3D v2 = MM * model.getVertexList()[face.getVertexIndexList()[1]].pos;
			Vec3D v3 = MM * model.getVertexList()[face.getVertexIndexList()[2]].pos;
			glVertex3f(v1.x, v1.y, v1.z);
			glVertex3f(v2.x, v2.y, v2.z);
			glVertex3f(v3.x, v3.y, v3.z);
		}
	}
	glEnd();

	glutSwapBuffers();
	glFlush();

	if (deltaFrame > 1000) {
		int fps = frameCount;
		std::cout << "FPS: " << fps << std::endl;
		frameCount = 0;
		lastFrame = currentFrame;
	}
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
	//gluLookAt(0.0, 10.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, -1.0); //hearth
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

	/*
	path.push_back({ Vec3D(0,0,0), Vec3D(0,0,-2), Vec3D(3,0,-2), Vec3D(3,0,0) });
	path.push_back({ Vec3D(3,0,0), Vec3D(3,0,1), Vec3D(2.8,0,1.5), Vec3D(0,0,3) });
	path.push_back({ Vec3D(0,0,3), Vec3D(-2.8,0,1.5), Vec3D(-3,0,1), Vec3D(-3,0,0) });
	path.push_back({ Vec3D(-3,0,0), Vec3D(-3,0,-2), Vec3D(0,0,-2), Vec3D(0,0,0) });

	for (auto &v : path) {
		for (double j = 0; j <= 1; j += 0.1) {
			Object3D p(filename1);

			p.scale(.01);
			p.setControlPoint();

			p.rotateX(270);
			p.setControlPoint();

			Vec3D newPos = Transformation::getCubicBezier(v[0], v[1], v[2], v[3], j);
			p.translate(newPos.x, newPos.y, newPos.z);
			p.setControlPoint();

			objectList.push_back(p);
		}
	}

	allPos = generatePositions(0.001);

	Object3D test(filename);
	test.setName("test");
	test.setColor(240, 230, 140);
	objectList.push_back(test);

	Object3D test2(filename);
	test2.setName("test2");
	test2.setColor(240, 230, 140);
	objectList.push_back(test2);

	Object3D test3(filename);
	test3.setName("test3");
	test3.setColor(240, 230, 140);
	objectList.push_back(test3);

	Object3D test4(filename1);
	test4.scale(0.6); //these are custom functions, used for effects pre-rendering :)
	test4.setControlPoint();
	test4.translate(0, 0, 1);
	test4.setControlPoint();
	objectList.push_back(test4);
	*/

	Object3D cube(filename3);
	objectList.push_back(cube);
	Mesh model = cube.getMesh();

	for (Face& face : model.getFaceList()) {
		Object3D p(filename1);

		p.scale(0.1);
		p.setControlPoint();

		p.rotateX(270);
		p.setControlPoint();

		Vec3D newPos = face.getNormal();
		p.translate(newPos.x, newPos.y, newPos.z);
		p.setControlPoint();

		objectList.push_back(p);
	}

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
