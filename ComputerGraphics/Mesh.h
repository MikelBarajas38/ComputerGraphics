#pragma once

#include <vector>
#include <string>
#include "Face.h"
#include "Vertex.h"

class Mesh
{
public:
	std::string getName() { return this->name; }
	void setName(std::string _name);
	std::vector<Vertex>& getVertexList() { return this->vertexList; }
	std::vector<Face> & getFaceList() { return this->faceList; }
	void addVertex(Vertex vertex);
	void addFace(Face face);
	void printObj();
	void assignRandomColor();

private:
	std::string name;
	std::vector<Vertex> vertexList;
	std::vector<Face> faceList;
	float randomFloat();
};

