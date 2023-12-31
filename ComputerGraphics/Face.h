#pragma once

#include<vector>
#include "Vec3D.h"

class Face
{
	public:
		void addIndex(int index);
		std::vector<int>& getVertexIndexList() { return this->vertexIndexList; }
		float *getColor() { return this->color; }
		void setColors(float R, float G, float B);

	private:
		std::vector<int> vertexIndexList;
		float color[4];

};

