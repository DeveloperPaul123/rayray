#pragma once
#include "raytracer/image/image.h"
#include <string>
namespace rayray
{
	/**
	 * @brief Write a given image to a ppm image file. 
	 * @param image the image to write.
	 * @param output_file full path to the output file. 
	 */
	bool write_ppm_image(const image<unsigned char> &image, const std::string &output_file);
}