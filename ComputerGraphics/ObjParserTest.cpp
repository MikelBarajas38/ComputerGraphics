#include <iostream>

#include"ObjParser.h"
#include"Mesh.h"

int test() {
	std::string filename = "C:\\Users\\mikel\\OneDrive\\Escritorio\\computer graphics\\v3\\untitled.obj";
	Mesh mesh = ObjParser::parse(filename);
	mesh.printObj();
	return 0;
}