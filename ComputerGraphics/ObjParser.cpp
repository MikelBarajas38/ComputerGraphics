#include "ObjParser.h"

#include <fstream>
#include <sstream>

Mesh ObjParser::parse(std::string filename) {

	std::ifstream file(filename);

	if (!file)
	{
		throw std::invalid_argument("Could not find file.");
		return Mesh();
	}

	Mesh mesh;

	std::string line;
	while (std::getline(file, line)) {

		std::stringstream ss(line);

		if (ss.eof()) {
			continue;
		}

		std::string type;
		ss >> type;

		if (type[0] == '#') {
			continue;
		}

		//cases

		if (type == "o") {

			std::string meshName;
			ss >> std::ws >> meshName;
			if (!ss.fail()) {
				mesh.setName(meshName);
			}

		}
		else if (type == "v") {

			double x, y, z;
			ss >> std::ws >> x >> std::ws >> y >> std::ws >> z;

			if (!ss.fail()) {
				mesh.addVertex(Vertex(x, y, z));
			}

		}
		else if (type == "f") {
			std::vector<std::string> indexes;

			while (!ss.eof())
			{
				std::string index;
				ss >> std::ws >> index;
				if (index.empty()) continue;
				indexes.push_back(index);
			}

			if (!ss.fail() || !indexes.empty()) {
				Face newFace;
				for (std::string& index : indexes) {
					newFace.addIndex(std::stoi(index.substr(0, index.find("/"))) - 1);
				}
				mesh.addFace(newFace);
			}
		}

	}

	return mesh;
}