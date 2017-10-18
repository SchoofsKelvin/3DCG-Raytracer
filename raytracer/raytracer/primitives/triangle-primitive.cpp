#include "primitives/triangle-primitive.h"
#include "util/misc.h"
#include "math/coordinate-systems.h"
#include "math/quadratic_equation.h"
#include "performance/performance.h"
#include <assert.h>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
    class TriangleImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
		Point3D x, y, z;
		Vector3D normal;

		TriangleImplementation(const Point3D x, const Point3D y, const Point3D z)
			: x(x), y(y), z(z) {
			normal = (y - x).cross(z - x).normalized();
		}

		std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override {
			std::vector<std::shared_ptr<Hit>> hits;

			auto t = (x - ray.origin).dot(normal) / ray.direction.dot(normal);
			auto h = ray.origin + ray.direction * t;
			if ((y - x).cross(h - x).dot(normal) < 0) return hits;
			if ((z - y).cross(h - y).dot(normal) < 0) return hits;
			if ((x - z).cross(h - z).dot(normal) < 0) return hits;
			auto hit = std::make_shared<Hit>();

			initialize_hit(hit.get(), ray, t);
			hits.push_back(hit);
			return hits;
		}

		bool find_first_positive_hit(const Ray& ray, Hit* hit) const override {
			auto t = (x - ray.origin).dot(normal) / ray.direction.dot(normal);
			auto h = ray.origin + ray.direction * t;
			if ((y - x).cross(h - x).dot(normal) < 0) return false;
			if ((z - y).cross(h - y).dot(normal) < 0) return false;
			if ((x - z).cross(h - z).dot(normal) < 0) return false;
			initialize_hit(hit, ray, t);
			return true;
		}

		math::Box bounding_box() const override
		{
			double x_min = std::min({ x.x(), y.x(),z.x() });
			double y_min = std::min({ x.x(), y.x(),z.x() });
			double z_min = std::min({ x.x(), y.x(),z.x() });

			double x_max = std::max({ x.x(), y.x(),z.x() });
			double y_max = std::max({ x.x(), y.x(),z.x() });
			double z_max = std::max({ x.x(), y.x(),z.x() });

			auto x = interval(x_min, x_max);
			auto y = interval(y_min, y_max);
			auto z = interval(z_min, z_max);

            return Box(x, y, z);
        }

    private:
        void initialize_hit(Hit* hit, const Ray& ray, double t) const
        {
            hit->t = t;
            hit->position = ray.at(t);
            hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(0, 0);
			hit->normal = normal;
            // hit->local_position.uv = compute_uv_from_xyz(hit->position);
			// hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
        }
    };
}

Primitive raytracer::primitives::triangle(const Point3D x, const Point3D y, const Point3D z)
{
    return Primitive(std::make_shared<TriangleImplementation>(x,y,z));
}
