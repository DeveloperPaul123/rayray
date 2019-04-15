#include "raytracer/geometry/plane.h"
#include "raytracer/core/shade_rec.h"

const double rayray::plane::k_epsilon = 0.000001;

rayray::plane::plane(const point<double, 3> &point, const vector<double, 3> &normal)
	: geometric_object(), point_(point), normal_(normal)
{
	
}

bool rayray::plane::hit(const rayray::ray& ray, double& t_min, rayray::shade_rec& sr) const
{
	const auto t = dot(point_ - ray.origin(), normal_ / dot(ray.direction(), normal_));
	if(t > k_epsilon)
	{
		t_min = t;
		sr.normal = normal_;
		sr.local_hit_point = (ray.origin() + t * ray.direction()).to_point();
		
		return true;
	}
	return false;
}

