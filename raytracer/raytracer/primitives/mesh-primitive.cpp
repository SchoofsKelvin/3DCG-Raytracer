#include "primitives/mesh-primitive.h"
#include "easylogging++.h"
#include <algorithm>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

Primitive raytracer::primitives::make_mesh(std::vector<gg::triangle>& triangles)
{
	std::vector<Primitive> &primitives = std::vector<Primitive>();
	for each (gg::triangle t in triangles)
	{
		Point3D a = Point3D(t.x1, t.y1, t.z1);
		Point3D b = Point3D(t.x2, t.y2, t.z2);
		Point3D c = Point3D(t.x3, t.y3, t.z3);
		Primitive t = triangle(a,b,c);
		primitives.push_back(t);
	}
	return make_union(primitives);
}
