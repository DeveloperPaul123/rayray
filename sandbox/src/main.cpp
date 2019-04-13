
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
#include "raytracer/tracers/ray_cast_tracer.h"
#include "raytracer/lights/point_light.h"
#include "raytracer/materials/matte_material.h"

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
    camera.set_lookat(-5, 0, 0);
    camera.set_view_plane_distance(1750.0);
    camera.compute_uvw();

    rayray::scene basic_scene;
    basic_scene.set_background_color(rayray::black());

    rayray::view_plane view_plane(400, 400, 1.0, 1.0);
    
    // initialize the sampler and generate the samples
    rayray::multijittered_sampler sampler(25); 
    sampler.generate_samples();

    view_plane.set_sampler(&sampler);
    basic_scene.set_view_plane(view_plane);

    rayray::ray_cast_tracer scene_tracer(&basic_scene);
    basic_scene.set_tracer(&scene_tracer);

    rayray::ambient_light amb_light;
    amb_light.set_radiance_scaling(1.0);
    amb_light.set_color({ 1.0, 1.0, 1.0 });

    basic_scene.set_ambient_light(&amb_light);

    rayray::point_light pt_light;
    pt_light.set_location({ 100, -100, 150 });
    pt_light.set_radiance_scaling(3.0);
    basic_scene.add_light(&pt_light);

    rayray::matte matte_material;
    matte_material.set_ka(0.25);
    matte_material.set_kd(0.65);
    matte_material.set_cd(1.0, 0.0, 0.0);

    rayray::matte matte_blue;
    matte_blue.set_ka(0.35);
    matte_blue.set_kd(0.55);
    matte_blue.set_cd(0.0, 0.0, 1.0);

    rayray::sphere sp1({ 10.0, -5.0, 0.0 }, 27.0);
    sp1.set_material(&matte_material);
   
    rayray::sphere sp2({ -10.0, -10.0, -50.0 }, 30.0);
    sp2.set_material(&matte_blue);

	// add objects to scene.
    basic_scene.add_object(&sp1);
	basic_scene.add_object(&sp2);

    const auto output_image = camera.render_scene(basic_scene);

	const auto ok = rayray::io::write_ppm_image(output_image, "output.ppm");

	if(!ok)
	{
		std::cout << "Could not output image." << std::endl;
        return -1;
	}

	return 0;
}
