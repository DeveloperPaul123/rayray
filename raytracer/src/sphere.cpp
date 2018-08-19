#include "raytracer/geometry/sphere.h"
#include "raytracer/core/shade_rec.h"

const double rayray::sphere::k_epsilon = 0.000001;

rayray::sphere::sphere(const point<double, 3>& center, const double& radius)
	: center_(center), radius_(radius)
{
	
}

bool rayray::sphere::hit(const rayray::ray& ray, double& t_min, rayray::shade_rec& sr) const
{
	// remember that a ray can be parameterized as origin + t * direction
	// "t" is the ray parameter. 
	// to solve for t using the equation for a sphere leads to a quadratic of the form
	// a*t^2 + b*t + c = 0 To solve for t use the quadratic formula
	// t = ((-b +- (b^2 - 4*a*c)^1/2) / 2 * a
	// the discriminant of the quadratic tells you how many times the ray hits the sphere
	// d = b^2 - 4 * a * c
	// d < 0 -> no hits
	// d = 0 -> one hit
	// d > 0 -> two hits
	
	auto temp = ray.origin() - center_;

	auto a = dot(ray.direction(), ray.direction());
	auto b = 2.0 * dot(temp, ray.direction());
	auto c = dot(temp, temp) - radius_ * radius_;

	auto disc = b * b - 4.0 * a * c;

	if(disc < 0.0)
	{
		return false;
	}

	double e = std::sqrt(disc);
	double denominator = 2.0 * a;

	auto t = (-b - e) / denominator; // smaller root

	if(t > k_epsilon)
	{
		t_min = t;
		sr.normal = (temp + t * ray.direction()) / radius_;
		sr.local_hit_point = ray.origin() + t * ray.direction();
		return true;
	}

	t = (-b + e) / denominator; // larger root

	if(t > k_epsilon)
	{
		t_min = t;
		sr.normal = (temp + t * ray.direction()) / radius_;
		sr.local_hit_point = ray.origin() + t * ray.direction();
		return true;
	}
	return false;
}
