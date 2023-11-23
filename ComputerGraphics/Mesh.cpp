#include "Mesh.h"

#include<iostream>
#include <iomanip>

void Mesh::addVertex(Vertex vertex) {
	vertexList.push_back(vertex);
}

void Mesh::addFace(Face face) {
	faceList.push_back(face);
}

void Mesh::setName(std::string _name) {
	name = _name;
}

void Mesh::printObj() {
	std::cout << "o " << name << "\n";

	for (Vertex& vertex : vertexList) {
		std::cout << std::fixed << std::setprecision(2) << "v " << vertex.pos.x << " " << vertex.pos.y << " " << vertex.pos.z << "\n";
	}

	for (Face& face : faceList) {
		std::cout << "f ";
		for (int& index : face.getVertexIndexList()) {
			std::cout << index + 1 << " ";
		}
		std::cout << "\n";
	}
}

float Mesh::randomFloat()
{
	return (float)(rand()) / (float)(rand());
}

void Mesh::assignRandomColor()
{
	for (Face& face : faceList) {
		face.setColors(randomFloat(), randomFloat(), randomFloat());
	}
}

void Mesh::setColor(double r, double g, double b)
{
	for (Face& face : faceList) {
		face.setColors(r, g, b);
	}
}

Vec3D Mesh::getMidPoint()
{
	double sumX = 0.0, sumY = 0.0, sumZ = 0.0;
	size_t numVertices = vertexList.size();

	for (const Vertex& vertex : vertexList) {
		sumX += vertex.pos.x;
		sumY += vertex.pos.y;
		sumZ += vertex.pos.z;
	}

	return Vec3D(sumX / numVertices, sumY / numVertices, sumZ / numVertices);
}

//this assumes all data has been set
void Mesh::init()
{
	/*
	for (Face& face : faceList) {

		//get normal
		Vec3D v1 = vertexList[face.getVertexIndexList()[0]].pos;
		Vec3D v2 = vertexList[face.getVertexIndexList()[1]].pos;
		Vec3D v3 = vertexList[face.getVertexIndexList()[2]].pos;

		Vec3D a = v2 - v1;
		Vec3D b = v3 - v1;

		face.setNormal(a.cross(b).norm());

	}
	*/
}
