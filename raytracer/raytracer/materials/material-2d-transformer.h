#pragma once

#include "imaging/color.h"
#include "math/point.h"
#include "math/function.h"
#include "math/transformation2d.h"
#include "primitives/hit-position.h"
#include "materials/material-properties.h"
#include "animation/time-stamp.h"
#include <assert.h>
#include <memory>
#include "material.h"


namespace raytracer
{
    class Material2DTransformer : public materials::_private_::MaterialImplementation
    {
    public:
        explicit Material2DTransformer(Material material, math::Transformation2D transformation)
            : material(material), transformation(transformation) { }

		MaterialProperties at(const HitPosition&) const override;

    private:
        Material material;
		math::Transformation2D transformation;
    };

	namespace materials
	{
		Material scale(const math::Vector2D, const Material);
		Material translate(const math::Vector2D, const Material);
		Material rotate(const math::Angle, const Material);
	}
}
