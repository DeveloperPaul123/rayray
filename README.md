# rayray

[![Build status](https://ci.appveyor.com/api/projects/status/d3yx9e3kj2ktexgr/branch/master?svg=true)](https://ci.appveyor.com/project/DeveloperPaul123/rayray/branch/master)

rayray is a baby raytracer I've been working on in my spare time. The goal is to create a decent raytracer in pure C++ 17. The current API is under heavy development but check back soon for updates!

Currently, the API looks something like this:

````cpp
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
````

