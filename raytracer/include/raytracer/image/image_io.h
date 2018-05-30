#pragma once
#include "raytracer/image/image.h"
#include <string>
namespace rayray
{
	bool write_ppm_image(const image<unsigned char> &image, const std::string &output_file);
}