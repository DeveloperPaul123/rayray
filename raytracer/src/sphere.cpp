#include "raytracer/geometry/sphere.h"

rayray::sphere::sphere(const point<double, 3>& center, const double& radius)
	: center_(center), radius_(radius)
{
	
}

bool rayray::sphere::hit(const rayray::ray& ray, double& t_min, rayray::shade_rec& sr) const
{
	// TODO
	return false;
}
