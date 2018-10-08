
#include <raytracer/core/ray.h>
#include <memory>
#include <iostream>
#include <fstream>
#include "raytracer/image/image.h"
#include "raytracer/image/image_io.h"
#include "raytracer/core/scene.h"
#include "raytracer/tracers/single_sphere_tracer.h"
#include "raytracer/core/scene_renderer.h"
#include "raytracer/tracers/multi_object_tracer.h"
#include "raytracer/geometry/plane.h"

rayray::vector<double, 3> color(const rayray::ray & r)
{
	using vec3 = rayray::vector<double, 3>;
	auto unit_direction = r.direction().to_unit_vector();
	const auto t = 0.5 * (unit_direction.y() + 1.0);
	return (t)*vec3({ 1.0, 1.0, 1.0 }) + (1.0 - t) * vec3({ 0.5, 0.7,1.0 });
}

int main(int argc, char* argv[])
{
	using vec3 = rayray::vector<double, 3>;
	using uchar = unsigned char;
	const std::string output = "output.ppm";

    rayray::sphere sp1({ 0.0, -25.0, 0.0 }, 80.0);
    sp1.set_color(rayray::red());

    rayray::sphere sp2({ 0, 30, 0 }, 60);
    sp2.set_color(rayray::yellow());

    rayray::plane plane({ 0, 0, 0 }, { 0, 1, 1 });
    plane.set_color({ 0.0, 0.3,0.0 });

    rayray::scene basic_scene;
    basic_scene.add_object(&sp1);
    basic_scene.add_object(&sp2);
    basic_scene.add_object(&plane);

    rayray::multi_object_tracer multi_object_tracer(&basic_scene);
    rayray::scene_renderer sphere_renderer(&basic_scene, &multi_object_tracer);
    auto output_image = sphere_renderer.render<unsigned char>();
	const auto ok = rayray::write_ppm_image(output_image, output);

	if(!ok)
	{
		std::cout << "Could not output image." << std::endl;
	}
	return 0;
}
