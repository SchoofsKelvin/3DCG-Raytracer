#include "demos/basic-sample-RTv3.h"
#include "demos/demo.h"
#include "util/lazy.h"
#include "easylogging++.h"

using namespace raytracer;
using namespace animation;
using namespace math;
using namespace imaging;
using namespace demos;


namespace
{
    class MeshDemo : public Demo
    {
    public:
        // C++ allows you to copy a superclass's constructor
        using Demo::Demo;

    protected:
        /// <summary>
        /// Creates the root. This method will be called for several values of <paramref name="now" />,
        /// thus creating an animation.
        /// </summary>
        raytracer::Primitive create_root(TimeStamp now) override
        {
            // Local imports. Allows us to write sphere() instead of raytracer::primitives::sphere()
            using namespace raytracer::primitives;
            using namespace raytracer::materials;

			auto material1 = uniform(MaterialProperties(
				colors::red() * 0.8,      // ambient lighting, not supported yet
				colors::black(),      // diffuse lighting, not supported yet
				colors::white() * 0.2,      // specular highlights, not supported yet
				10                     // specular exponent, not supported yet
			));
			auto material2 = uniform(MaterialProperties(
				colors::green() * 0.6,      // ambient lighting, not supported yet
				colors::black(),      // diffuse lighting, not supported yet
				colors::white() * 0.8,      // specular highlights, not supported yet
				10                     // specular exponent, not supported yet
			));

			auto material = vertical_lines(0.5, material1, material2);

            // Create an animation of a double going from -5.0 to 5.0 in 1 second
            // It is important to write 5.0 and not 5, otherwise it will create an animation of ints instead of doubles
            auto x_position = animation::animate(-5.0, 5.0, 1_s);

			Primitive primitive = xz_plane();

            // Move the sphere. x_position(now) = asks the animation what x at this point in time
            //primitive = translate(Vector3D(x_position(now), 0, 0), primitive);

            // Assign a material to the sphere
            primitive = decorate(material, primitive);

            return primitive;
        }

        /// <summary>
        /// Creates light sources.
        /// </summary>
        std::vector<raytracer::LightSource> create_light_sources(TimeStamp now) override
        {
            // Local import
            using namespace raytracer::lights;

            std::vector<LightSource> light_sources;

			light_sources.push_back(raytracer::lights::omnidirectional(Point3D(0, 0, 10), colors::white()));
			light_sources.push_back(raytracer::lights::omnidirectional(Point3D(10, 0, 0), colors::white()));

            // No lights

            return light_sources;
        }

        /// <summary>
        /// Creates camera.
        /// </summary>
        raytracer::Camera create_camera(TimeStamp) override
        {
            return raytracer::cameras::perspective(
                Point3D(0, 5, 10),         // position of eye
                Point3D(0, 0, 0),          // point the camera looks at
                Vector3D(0, 1, 0),         // up-vector: indicates camera is "standing up"
                1,                         // distance between eye and viewing plane
                1                          // aspect ratio
            );
        }

		RayTracer create_ray_tracer() override {
			return raytracers::v3();
		}

    private:
        Primitive m_mesh;
    };
}

void demos::basic_sample_RTv3(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
{
    MeshDemo(500, 1_s, 5, 1).render(output);
}
