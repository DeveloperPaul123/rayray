
#include <raytracer/core/ray.h>
#include <iostream>
#include "raytracer/image/image.h"
#include "raytracer/image/image_io.h"
#include "raytracer/core/scene.h"
#include "raytracer/core/scene_renderer.h"
#include "raytracer/tracers/multi_object_tracer.h"
#include "raytracer/geometry/plane.h"
#include "raytracer/samplers/jittered_sampler.h"
#include "raytracer/samplers/multijittered_sampler.h"
#include "raytracer/cameras/pinhole_camera.h"

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

    rayray::pinhole_camera camera;
    camera.set_eye(0, 0, 500);
    camera.set_lookat(0, 0, 0);
    camera.set_view_plane_distance(500);
    camera.compute_uvw();

    rayray::sphere sp1({ -45.0, 45.0, 40.0 }, 50.0);
    sp1.set_color(rayray::red());

    rayray::scene basic_scene;
    basic_scene.add_object(&sp1);
    basic_scene.set_background_color({ 0.0, 0.0, 1.0 });

    rayray::view_plane view_plane(300, 300, 1.0, 1.0);

    // initialize the sampler and generate the samples
    rayray::multijittered_sampler sampler(25); 
    sampler.generate_samples();

    view_plane.set_sampler(&sampler);
    basic_scene.set_view_plane(view_plane);

    rayray::multi_object_tracer multi_object_tracer(&basic_scene);
    basic_scene.set_tracer(&multi_object_tracer);

    auto output_image = camera.render_scene(basic_scene);

	const auto ok = rayray::io::write_ppm_image(output_image, "output.ppm");

	if(!ok)
	{
		std::cout << "Could not output image." << std::endl;
        return -1;
	}

	return 0;
}
