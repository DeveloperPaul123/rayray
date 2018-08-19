#include "raytracer/image/image_io.h"
#include <fstream>

namespace rayray
{
	bool write_ppm_image(const image<unsigned char> &image, const std::string &output_file)
	{
		std::ofstream output;
		try
		{
			output.open(output_file, std::ios_base::out);
			const char new_line = '\n';
			output << "P3" << new_line;
			output << image.width() << " " << image.height() << new_line;
			output << "255" << new_line; // max value
			for(auto r = 0; r < image.height(); r++)
			{
				for(auto c = 0; c < image.width(); c++)
				{
					output << int(image.at(r, c, 0)) << " ";
					output << int(image.at(r, c, 1)) << " ";
					output << int(image.at(r, c, 2));
					if(c < image.width() - 1)
					{
						output << " ";
					}
					else
					{
						output << new_line;
					}
				}
			}

			output.close();
			return true;
		}
		catch(std::exception)
		{
			return false;
		}
	}
}
