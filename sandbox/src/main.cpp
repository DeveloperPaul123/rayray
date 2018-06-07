
#include <raytracer/core/ray.h>
#include <memory>
#include <iostream>
#include <fstream>
#include "raytracer/image/image.h"
#include "raytracer/image/image_io.h"

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
	const std::string output_file = "output.ppm";

	const auto width = 200;
	const auto height = 100;
	auto output_image = rayray::image<uchar>(width, height);

	const vec3 lower_left_corner({ -2.0, -1.0, -1.0 });
	const vec3 horizontal({ 4.0, 0.0, 0.0 });
	const vec3 vertical({ 0.0, 2.0, 0.0 });
	const vec3 origin({ 0.0, 0.0, 0.0 });

	for(auto j = 0; j < height; j++)
	{
		for(auto i = 0; i < width; i++)
		{
			auto u = double(i) / double(width);
			auto v = double(j) / double(height);

			const rayray::ray ray(origin, lower_left_corner + u * horizontal + v * vertical);
			auto col = color(ray);

			const auto ir = int(255.99 * col[0]);
			const auto ig = int(255.99 * col[1]);
			const auto ib = int(255.99 * col[2]);
			
			output_image.set(j, i, rayray::channel::red, uchar(ir));
			output_image.set(j, i, rayray::channel::green, uchar(ig));
			output_image.set(j, i, rayray::channel::blue, uchar(ib));
		}
	}

	const auto ok = rayray::write_ppm_image(output_image, output_file);

	if(!ok)
	{
		std::cout << "Could not output image." << std::endl;
	}
	return 0;
}
