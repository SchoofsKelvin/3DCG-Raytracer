#pragma once

#include "raytracers/ray-tracer.h"
#include "raytracers/ray-tracer-v4.h"
#include <memory>

using namespace imaging;
using namespace math;


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV5 : public RayTracerV4
            {
            public:
				TraceResult trace(const Scene&, const math::Ray&) const override;
				TraceResult trace(const Scene&, const math::Ray&, const double) const;
				Color compute_reflection(const Scene&, const MaterialProperties &, const Hit&, const Ray&, const double) const;
            };
        }

        /// <summary>
        /// Creates simplest ray tracer.
        /// </summary>
        RayTracer v5();
    }
}