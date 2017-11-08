#include "ray-tracer-v4.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


TraceResult raytracer::raytracers::_private_::RayTracerV4::trace(const Scene& scene, const Ray& ray) const
{
	Hit hit;

	// Ask the scene for the first positive hit, i.e. the closest hit in front of the eye
	// If there's a hit, find_first_positive_hit returns true and updates the hit object with information about the hit
	if (scene.root->find_first_positive_hit(ray, &hit))
	{
		// There's been a hit
		// Fill in TraceResult object with information about the trace

		Color result = colors::black();
		MaterialProperties props = hit.material->at(hit.local_position);

		result += compute_ambient(props);
		result += process_lights(scene, props, hit, ray);

		// The hit object contains the group id, just copy it (group ids are important for edge detection)
		unsigned group_id = hit.group_id;

		// The t-value indicates where the ray/scene intersection took place.
		// You can use ray.at(t) to find the xyz-coordinates in space.
		double t = hit.t;

		// Group all this data into a TraceResult object.
		return TraceResult(result, group_id, ray, t);
	}
	else
	{
		// The ray missed all objects in the scene
		// Return a TraceResult object representing "no hit found"
		// which is basically the same as returning black
		return TraceResult::no_hit(ray);
	}
}

Color raytracer::raytracers::_private_::RayTracerV4::process_light_ray(const Scene &scene, const MaterialProperties &props, const Hit &hit, const Ray &ray, const LightRay &lray) const
{
	Hit lhit;
	scene.root->find_first_positive_hit(lray.ray, &lhit);
	if (lhit.t >= 0 && lhit.t < 0.99999) return colors::black();
	return RayTracerV3::process_light_ray(scene, props, hit, ray, lray);
}


raytracer::RayTracer raytracer::raytracers::v4()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV4>());
}
