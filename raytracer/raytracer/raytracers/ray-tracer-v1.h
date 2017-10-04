#pragma once

#include "raytracers/ray-tracer.h"
#include <memory>

using namespace imaging;


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV1 : public RayTracerImplementation
            {
            public:
                TraceResult trace(const Scene&, const math::Ray&) const override;
				Color compute_ambient(const MaterialProperties&) const;
            };
        }

        /// <summary>
        /// Creates simplest ray tracer.
        /// </summary>
        RayTracer v1();
    }
}