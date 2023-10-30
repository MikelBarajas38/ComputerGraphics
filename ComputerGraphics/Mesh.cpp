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
