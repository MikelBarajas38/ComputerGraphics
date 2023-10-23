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
		std::cout << std::fixed << std::setprecision(2) << "v " << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
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