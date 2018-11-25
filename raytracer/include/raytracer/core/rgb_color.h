#pragma once

#include "raytracer/core/nd_base.h"

namespace rayray
{
	class color_exception : public std::exception
	{
		public:
			color_exception();
			const char* what() const noexcept override;
	};
	
	class rgb_color : public nd_base<double, 3>
	{
	public:
		rgb_color();
		rgb_color(const double &red, const double &green, const double &blue);
		double red() const;
		double green() const;
		double blue() const;
		rgb_color operator^(const double& value) const;
	};

#pragma region Utility functions
	rgb_color blue();
	rgb_color black();
	rgb_color red();
	rgb_color green();
	rgb_color yellow();
	rgb_color operator*(const rgb_color &first, const rgb_color &second);
    rgb_color operator*(const double &scaling, const rgb_color &color);
    rgb_color operator*(const rgb_color &color, const double &scaling);
#pragma endregion
}