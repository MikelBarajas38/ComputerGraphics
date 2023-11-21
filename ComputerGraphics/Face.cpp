#include "Face.h"

void Face::addIndex(int index) {
	vertexIndexList.push_back(index);
}

void Face::setColors(float R, float G, float B) {
	color[0] = R;
	color[1] = G;
	color[2] = B;
}

Vec3D Face::getNormal()
{
	return normal;
}

void Face::setNormal(Vec3D _normal)
{
	normal = _normal;
}
