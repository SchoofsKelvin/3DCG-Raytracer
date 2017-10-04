#pragma once

#include "raytracers/ray-tracer.h"
#include "raytracers/ray-tracer-v2.h"
#include <memory>

using namespace imaging;
using namespace math;


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV3 : public RayTracerV2
            {
            public:
                TraceResult trace(const Scene&, const math::Ray&) const override;
				Color process_light_ray(const Scene&, const MaterialProperties&, const Hit&, const Ray&, const LightRay&) const override;
				Color compute_specular(const MaterialProperties&, const Hit&, const Ray&, const LightRay&) const;
            };
        }

        /// <summary>
        /// Creates simplest ray tracer.
        /// </summary>
        RayTracer v3();
    }
}