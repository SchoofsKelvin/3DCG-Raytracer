#include "materials/material-2d-transformer.h"

using namespace math;
using namespace raytracer;
using namespace raytracer::materials;

MaterialProperties raytracer::Material2DTransformer::at(const HitPosition &hit) const
{
	Point2D point = hit.uv;
	point = transformation.transformation_matrix * point;
	return material->at(hit);
}
