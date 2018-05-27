
#include <raytracer/core/ray.h>
#include <memory>
#include <iostream>

rayray::vector<double, 3> color(const rayray::ray & r)
{
	using vec3 = rayray::vector<double, 3>;
	auto unit_direction = r.direction().to_unit_vector();
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t)*vec3({ 1.0, 1.0, 1.0 }) + t * vec3({ 0.5, 0.7,1.0 });
}
void write_ppm_image(unsigned char* data, const int &width, const int &height, const std::string &file_name)
{
	
}

int main(int argc, char* argv[])
{
	using vec3 = rayray::vector<double, 3>;

	const auto width = 20;
	const auto height = 10;
	auto image_data = std::make_unique<unsigned char[]>(width*height);

	const vec3 lower_left_corner({ -2.0, -1.0, -1.0 });
	const vec3 horizontal({ 4.0, 0.0, 0.0 });
	const vec3 vertical({ 0.0, 2.0, 0.0 });
	const vec3 origin({ 0.0, 0.0, 0.0 });

	std::cout << "P3\n" << width << " " << height << "\n255\n";

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

			std::string delimiter = i < width-1 ? " " : "\n";
			std::cout << ir << " " << ig << " " << ib << delimiter.data();
		}
	}
	return 0;
}
