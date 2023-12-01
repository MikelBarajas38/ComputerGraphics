#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>  

#include "Object3D.h"
#include "Transformation.h"
#include "DirectionalLight.h"
#include "Camera.h"

//3D objects in scene

std::vector<Object3D> objectList;

// Trayectories

std::vector<std::vector<Vec3D>> path;
int current = 0;

std::vector<Vec3D> allPos;
int posi = 0;

// time and animation stuff

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

// lightning

float ambientLight[4] = { 1.0, 1.0, 1.0, 0.0 };
std::vector<DirectionalLight> directionalLightList;

// phong shading
std::vector<Vec3D> vertexNormals;
std::vector<int> adyacentFaces;

// camera
std::vector<Camera> views;
Camera camera;
int current_camera = 0;
Vec3D viewDir;

// user input

bool usePhong = false;
bool computeDirectional = true;
bool computeSpecular = true;
int model = 1;

float* computeFinalColor(float* color, Vec3D& normal)
{
	float Intensity[4] = { ambientLight[0] * color[0] , ambientLight[1] * color[1] , ambientLight[2] * color[2], 0.0 };

	for (DirectionalLight& light : directionalLightList) {

		float diff = -light.getDirection().dot(normal);

		if (computeDirectional) {
			Intensity[0] += light.getIntensity()[0] * diff;
			Intensity[1] += light.getIntensity()[1] * diff;
			Intensity[2] += light.getIntensity()[2] * diff;
		}

		if (computeSpecular) {
			Vec3D reflectDir = (normal * (2 * (-diff))) - light.getDirection();
			float spec = pow(std::max(viewDir.dot(reflectDir), 0.0), light.getSpecularFactor());
			Intensity[0] += light.getIntensity()[0] * spec;
			Intensity[1] += light.getIntensity()[1] * spec;
			Intensity[2] += light.getIntensity()[2] * spec;
		}

	}

	return Intensity;
}

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

void discoBallAnimation(Object3D& ball)
{
	Matrix3D M = Transformation::RotationY(temp);

	ball.transform(M);

	temp += 0.1;
}

void discoBallAnimation2(Object3D& ball)
{
	Matrix3D M = Transformation::Translation(0.0, 0.0, 1.0) *
				 Transformation::RotationX(270) *
				 Transformation::RotationY(temp) *
				 Transformation::Scale(0.6, 0.6, 0.6);

	ball.transform(M);

	temp += 0.1;
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
		else if (object.getName() == "disco") {
			discoBallAnimation2(object);
		}

		if (!usePhong) {
			for (Face& face : object.getMesh().getFaceList()) {

				Vec3D v1 = object.getModelMatrix() * object.getMesh().getVertexList()[face.getVertexIndexList()[0]].pos;
				Vec3D v2 = object.getModelMatrix() * object.getMesh().getVertexList()[face.getVertexIndexList()[1]].pos;
				Vec3D v3 = object.getModelMatrix() * object.getMesh().getVertexList()[face.getVertexIndexList()[2]].pos;

				Vec3D a = v2 - v1;
				Vec3D b = v3 - v1;

				Vec3D normal = a.cross(b).norm();

				glColor4fv(computeFinalColor(face.getColor(), normal));

				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v2.x, v2.y, v2.z);
				glVertex3f(v3.x, v3.y, v3.z);
			}
		}
		else {

			int n_vertex = object.getMesh().getVertexList().size();
			vertexNormals.resize(n_vertex);
			adyacentFaces.resize(n_vertex);

			for (Face& face : object.getMesh().getFaceList()) {

				Vec3D v1 = object.getModelMatrix() * object.getMesh().getVertexList()[face.getVertexIndexList()[0]].pos;
				Vec3D v2 = object.getModelMatrix() * object.getMesh().getVertexList()[face.getVertexIndexList()[1]].pos;
				Vec3D v3 = object.getModelMatrix() * object.getMesh().getVertexList()[face.getVertexIndexList()[2]].pos;

				Vec3D a = v2 - v1;
				Vec3D b = v3 - v1;

				Vec3D normal = a.cross(b).norm();

				vertexNormals[face.getVertexIndexList()[0]] = vertexNormals[face.getVertexIndexList()[0]] + normal;
				vertexNormals[face.getVertexIndexList()[1]] = vertexNormals[face.getVertexIndexList()[1]] + normal;
				vertexNormals[face.getVertexIndexList()[2]] = vertexNormals[face.getVertexIndexList()[2]] + normal;

				adyacentFaces[face.getVertexIndexList()[0]]++;
				adyacentFaces[face.getVertexIndexList()[1]]++;
				adyacentFaces[face.getVertexIndexList()[2]]++;

			}

			for (Face& face : object.getMesh().getFaceList()) {

				for (int i = 0; i < 3; i++) {
					Vec3D v = object.getModelMatrix() * object.getMesh().getVertexList()[face.getVertexIndexList()[i]].pos;
					Vec3D vertexNormal = (vertexNormals[face.getVertexIndexList()[i]] * (1.0 / (double)adyacentFaces[face.getVertexIndexList()[i]])).norm();
					glColor4fv(computeFinalColor(face.getColor(), vertexNormal));
					glVertex3f(v.x, v.y, v.z);
				}

			}

			vertexNormals.clear();
			adyacentFaces.clear();

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

	gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
		camera.getLookAtX(), camera.getLookAtY(), camera.getLookAtZ(),
		camera.getUpX(), camera.getUpY(), camera.getUpZ());

	glEnable(GL_DEPTH_TEST);

}

void changeModel() {
	objectList.pop_back();
	std::string filename;

	if (model == 1) {
		filename = "torus.obj";
	}
	else if (model == 2) {
		filename = "goodstar.obj";
	}
	else {
		filename = "sphere.obj";
	}

	Object3D test4(filename);
	test4.setColor(237, 166, 196);
	test4.setName("disco");
	test4.setColor(60, 60, 60);
	objectList.push_back(test4);
	model = (model + 1) % 3;
}

void inputHandler(unsigned char key, int x, int y)
{
	switch (key) {
		case 'p':
			usePhong = !usePhong;
			break;
		case 's':
			computeSpecular = !computeSpecular;
			break;
		case 'd':
			computeDirectional = !computeDirectional;
			break;
		case 'c':
			current_camera = (current_camera + 1) % views.size();
			camera = views[current_camera];
			viewDir = camera.getDirection();
			init();
			break;
		case 'm':
			changeModel();
	}

}

void mouseHandler(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		changeModel();
	}
}

void initCamera()
{
	current_camera = 0;
	camera = views[current_camera];
	viewDir = camera.getDirection();
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
	std::string filename = "eyeless_star.obj";
	std::string filename1 = "dode.obj";
	std::string filename2 = "soda.obj";
	std::string filename3 = "FishBone.obj";
	std::string filename4 = "untitled.obj";
	std::string filename5 = "sphere.obj";
	std::string filename6 = "plane.obj";
	
	Object3D plane(filename6);
	plane.scale(100, 0, 100); //these are custom functions, used for effects pre-rendering :)
	plane.setColor(63, 15, 60);
	plane.setControlPoint();
	plane.translate(0, -10, 0);
	plane.setControlPoint();
	//objectList.push_back(plane);

	path.push_back({ Vec3D(0,0,0), Vec3D(0,0,-2), Vec3D(3,0,-2), Vec3D(3,0,0) });
	path.push_back({ Vec3D(3,0,0), Vec3D(3,0,1), Vec3D(2.8,0,1.5), Vec3D(0,0,3) });
	path.push_back({ Vec3D(0,0,3), Vec3D(-2.8,0,1.5), Vec3D(-3,0,1), Vec3D(-3,0,0) });
	path.push_back({ Vec3D(-3,0,0), Vec3D(-3,0,-2), Vec3D(0,0,-2), Vec3D(0,0,0) });

	for (auto &v : path) {
		for (double j = 0; j <= 1; j += 0.2) {
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

	Object3D test4(filename5);
	test4.setColor(237, 166, 196);
	test4.setName("disco");
	test4.setColor(60, 60, 60);
	objectList.push_back(test4);
	
	/*
	Object3D ball(filename5);
	ball.setName("disco");
	ball.setColor(60, 60, 60);
	objectList.push_back(ball);
	*/

	/*
	Object3D testpoint(filename1);
	testpoint.scale(0.6); //these are custom functions, used for effects pre-rendering :)
	testpoint.setControlPoint();
	testpoint.translate(0, -3, 0);
	testpoint.setControlPoint();
	testpoint.setColor(255, 0, 0);
	objectList.push_back(testpoint);

	Object3D testpoint2(filename1);
	testpoint2.scale(0.6); //these are custom functions, used for effects pre-rendering :)
	testpoint2.setControlPoint();
	testpoint2.translate(0, 0, 0);
	testpoint2.setControlPoint();
	testpoint2.setColor(0, 0, 255);
	objectList.push_back(testpoint2);
	*/

	DirectionalLight light1(Vec3D(3, 0, -1), Vec3D(0, 0, 0), 0.6, 0.6, 0.6, 10.0);
	directionalLightList.push_back(light1);

	DirectionalLight light2(Vec3D(-3, 0, 1), Vec3D(0, 0, 0), 0.2, 0.2, 0.4, 15.0);
	//directionalLightList.push_back(light2);

	DirectionalLight light4(Vec3D(-3, 1, -6), Vec3D(0, 0, 0), 0.9, 0.3, 0.3, 25.0);
	//directionalLightList.push_back(light4);

	DirectionalLight light3(Vec3D(3, 1, 6), Vec3D(0, 0, 0), 0.2, 0.6, 0.2, 25.0);
	directionalLightList.push_back(light3);

	Camera camera1(0.0, 10.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, -1.0);
	views.push_back(camera1);

	Camera camera2(10.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, -1.0);
	views.push_back(camera2);

	Camera camera3(8.0, 6.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, -1.0);
	views.push_back(camera3);

	Camera camera4(5.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	views.push_back(camera4);

	Camera camera1r(0.0, -10.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, -1.0);
	views.push_back(camera1r);

	Camera camera2r(-10.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, -1.0);
	views.push_back(camera2r);

	Camera camera3r(-8.0, -6.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, -1.0);
	views.push_back(camera3r);

	Camera camera4r(-5.0, 0.0, -5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	views.push_back(camera4r);

	initCamera();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(30, 30);
	glutCreateWindow("Computer Graphics");
	init();
	glutKeyboardFunc(inputHandler);
	glutMouseFunc(mouseHandler);
	glutDisplayFunc(display);
	//glutPostRedisplay();
	glutIdleFunc(display);
	glutMainLoop();

	return 0;   /* ISO C requires main to return int. */
}
