// MeshConverter.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>

#include "stdafx.h"
#include "tiny_obj_loader.h"
#include "gg.h"

using namespace gg;

int main() {
	std::string inputfile = "C:\\Users\\schoo_000\\Documents\\School\\2017-2018\\3D Computer Graphics\\Hi2.obj";
	std::string outputfile = "C:\\Users\\schoo_000\\Documents\\School\\2017-2018\\3D Computer Graphics\\Hi.gg";
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());

	if (!err.empty()) std::cerr << err << std::endl;

	if (!ret) exit(1);

	std::vector<triangle> triangles;

	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		std::cout << "Shape: " << s << std::endl;
		size_t index_offset = 0;
		auto idk = shapes[s].mesh.num_face_vertices[0];
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			int fv = shapes[s].mesh.num_face_vertices[f];

			std::cout << "\tFace: " << f << " with " << fv << " vertices" << std::endl;

			/*
			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
				tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
				tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
				tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
				tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
				tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
				tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
				tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];
				// Optional: vertex colors
				// tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
				// tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
				// tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
				std::cout << "\t\t" << vx << ", " << vy << ", " << vz << std::endl;
				std::cout << "\t\t\t" << nx << ", " << ny << ", " << nz << std::endl;
				std::cout << "\t\t\t" << tx << ", " << ty << std::endl;
			}
			*/

			tinyobj::index_t idx1 = shapes[s].mesh.indices[index_offset];
			tinyobj::real_t vx1 = attrib.vertices[3 * idx1.vertex_index + 0];
			tinyobj::real_t vy1 = attrib.vertices[3 * idx1.vertex_index + 1];
			tinyobj::real_t vz1 = attrib.vertices[3 * idx1.vertex_index + 2];

			tinyobj::index_t idx2 = shapes[s].mesh.indices[index_offset + 1];
			tinyobj::real_t vx2 = attrib.vertices[3 * idx2.vertex_index + 0];
			tinyobj::real_t vy2 = attrib.vertices[3 * idx2.vertex_index + 1];
			tinyobj::real_t vz2 = attrib.vertices[3 * idx2.vertex_index + 2];

			tinyobj::index_t idx3 = shapes[s].mesh.indices[index_offset + 2];
			tinyobj::real_t vx3 = attrib.vertices[3 * idx3.vertex_index + 0];
			tinyobj::real_t vy3 = attrib.vertices[3 * idx3.vertex_index + 1];
			tinyobj::real_t vz3 = attrib.vertices[3 * idx3.vertex_index + 2];
			triangle t = triangle{ vx1, vy1, vz1, vx2, vy2, vz2, vx3, vy3, vz3 };
			triangles.push_back(t);

			std::cout << "\t\t" << fv << "|" << index_offset << ": " << (idx1.vertex_index+1) << ", " << (idx2.vertex_index + 1) << ", " << (idx3.vertex_index + 1) << std::endl;
			std::cout << "\t\t" << vx1 << ", " << vy1 << ", " << vz1 << std::endl;
			std::cout << "\t\t" << vx2 << ", " << vy2 << ", " << vz2 << std::endl;
			std::cout << "\t\t" << vx3 << ", " << vy3 << ", " << vz3 << std::endl;

			index_offset += fv;

			// per-face material
			shapes[s].mesh.material_ids[f];
		}
		std::cout << "IDK: " << index_offset << " " << shapes[s].mesh.indices.size() << std::endl;
	}
	std::cout << shapes.size() << ", " << materials.size() << std::endl;
	std::cout << "#Triangles: " << triangles.size() << std::endl;
	writefile(&triangles, outputfile);
	std::cout << "Written to file, reading in again" << std::endl;
	auto gg = readfile(outputfile);
	std::cout << "#Triangles: " << gg.size() << std::endl;
	std::getchar();
	for each (triangle t in gg)
	{
		std::cout << t.x1 << ", " << t.y1 << ", " << t.z1 << std::endl;
		std::cout << t.x2 << ", " << t.y2 << ", " << t.z2 << std::endl;
		std::cout << t.x3 << ", " << t.y3 << ", " << t.z3 << std::endl;
		std::cout << std::endl << std::endl;
	}
	std::cout << "Program finished" << std::endl;
	std::getchar();
	return 0;
}
