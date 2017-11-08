#include "gg.h"

using namespace gg;

void gg::writefile(const std::vector<triangle> *triangles, std::string filename) {
	std::ofstream file(filename, std::ios::binary);
	int amount = triangles->size();
	file.write((char*)&amount, sizeof(amount));
	for each (triangle t in *triangles)
	{
		file.write((char*)&t, sizeof(triangle));
	}
	file.close();
}

std::vector<triangle> gg::readfile(std::string filename) {
	std::ifstream file(filename, std::ios::binary);
	int amount;
	file.read((char*)&amount, sizeof(amount));
	std::vector<triangle> triangles(amount);
	for (int i = 0; i < amount; i++)
	{
		triangle t;
		file.read((char*)&t, sizeof(triangle));
		triangles.push_back(t);
	}
	file.close();
	return triangles;
}
