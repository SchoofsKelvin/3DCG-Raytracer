#pragma once

#include <iostream>
#include <fstream>
#include <vector>

namespace gg {
	struct triangle {
		float x1, y1, z1;
		float x2, y2, z2;
		float x3, y3, z3;
	};

	void writefile(const std::vector<triangle> *triangles, std::string filename);

	std::vector<triangle> readfile(std::string filename);
}