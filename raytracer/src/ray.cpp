#include "raytracer/core/ray.h"

rayray::ray::ray(const vec3& origin, const vec3& direction)
	: origin_(origin), direction_(direction)
{
	
}

rayray::ray::vec3 rayray::ray::origin() const
{
	return origin_;
}

rayray::ray::vec3 rayray::ray::direction() const
{
	return direction_;
}


