#pragma once

#include<string>
#include "Mesh.H"

class ObjParser
{
	public:
		static Mesh parse(std::string filename);

};

