#include "Face.h"

void Face::addIndex(int index) {
	vertexIndexList.push_back(index);
}

void Face::setColors(float R, float G, float B) {
	color[0] = R;
	color[1] = G;
	color[2] = B;
}
