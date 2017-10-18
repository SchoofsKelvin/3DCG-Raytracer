#include "materials/material-2d-transformer.h"
#include "math/transformation-matrices.h"

using namespace math;
using namespace raytracer;
using namespace raytracer::materials;

MaterialProperties raytracer::Material2DTransformer::at(const HitPosition &hit) const
{
	HitPosition newhit = HitPosition(hit);
	newhit.uv = transformation.inverse_transformation_matrix * hit.uv;
	return material->at(newhit);
}

}
