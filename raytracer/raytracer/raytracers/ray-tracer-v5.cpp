#include "ray-tracer-v5.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


TraceResult raytracer::raytracers::_private_::RayTracerV5::trace(const Scene& scene, const Ray& ray) const {
	return trace(scene, ray, 1);
}
TraceResult raytracer::raytracers::_private_::RayTracerV5::trace(const Scene& scene, const Ray& ray, const double weight) const
{
	if (weight < 0.1) return TraceResult::no_hit(ray);

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
		result += compute_reflection(scene, props, hit, ray, weight);

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

Color raytracer::raytracers::_private_::RayTracerV5::compute_reflection(const Scene &scene, const MaterialProperties &props, const Hit &hit, const Ray &ray, const double weight) const
{
	if (props.reflectivity == 0) return colors::black();
	auto normal = hit.normal.normalized();
	auto dir = ray.direction - 2 * normal.dot(ray.direction) * normal;
	Ray nray(hit.position + dir * 0.00000001, dir);
	return props.reflectivity * trace(scene, nray, weight * props.reflectivity).color;
}


raytracer::RayTracer raytracer::raytracers::v5()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV5>());
}
