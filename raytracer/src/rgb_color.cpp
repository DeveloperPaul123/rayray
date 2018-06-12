#include "raytracer/core/rgb_color.h"

rayray::rgb_color::rgb_color()
	: nd_base<double, 3>(0.0) // default color is black
{
}

rayray::rgb_color::rgb_color(const double& red, const double& green, const double& blue)
	:nd_base<double, 3>({red, green, blue})
{
}

double rayray::rgb_color::red() const
{
	return data_[0];
}

double rayray::rgb_color::green() const
{
	return data_[1];
}

double rayray::rgb_color::blue() const
{
	return data_[2];
}

rayray::rgb_color rayray::rgb_color::operator^(const double& value) const
{
	return rgb_color(
		std::pow(red(), value),
		std::pow(green(), value),
		std::pow(blue(), value)
	);
}

rayray::rgb_color rayray::blue()
{
	return rgb_color( 0.0, 0.0, 1.0 );
}

rayray::rgb_color rayray::black()
{
	return rgb_color(0.0, 0.0, 0.0);
}

rayray::rgb_color rayray::red()
{
	return rgb_color(1.0, 0.0, 0.0);
}

rayray::rgb_color rayray::green()
{
	return rgb_color(0.0, 1.0, 0.0);
}

rayray::rgb_color rayray::yellow()
{
	return rgb_color(1.0, 1.0, 0.0);
}

rayray::rgb_color rayray::operator*(const rgb_color& first, const rgb_color& second)
{
	return rgb_color(first.red()*second.red(),
		first.green()*second.green(),
		first.blue()*second.blue());
}








