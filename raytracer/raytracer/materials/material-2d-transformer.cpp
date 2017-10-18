#include "materials/material-2d-transformer.h"
#include "math/transformation-matrices.h"

using namespace math;
using namespace raytracer;
using namespace raytracer::materials;

using namespace materials::_private_;

MaterialProperties raytracer::Material2DTransformer::at(const HitPosition &hit) const
{
	HitPosition newhit = HitPosition(hit);
	newhit.uv = transformation.inverse_transformation_matrix * hit.uv;
	return material->at(newhit);
}

Material raytracer::materials::scale(const Vector2D scale, const Material mat)
{
	Transformation2D trans = Transformation2D(transformation_matrices::scaling(scale.x(), scale.y()), transformation_matrices::scaling(1 / scale.x(), 1 / scale.y()));
	auto mi = std::make_shared<Material2DTransformer>(mat, trans);
	return Material(mi);
}

Material raytracer::materials::translate(const Vector2D translate, const Material mat)
{
	Transformation2D trans = Transformation2D(transformation_matrices::translation(translate), transformation_matrices::translation(-translate));
	auto mi = std::make_shared<Material2DTransformer>(mat, trans);
	return Material(mi);
}
