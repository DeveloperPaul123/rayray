#include "raytracer/tracers/single_sphere_tracer.h"
#include "raytracer/core/shade_rec.h"

rayray::single_sphere_tracer::single_sphere_tracer()
	: tracer()
{
	
}

rayray::single_sphere_tracer::single_sphere_tracer(scene* scene_ptr)
	: tracer(scene_ptr)
{
	
}

rayray::rgb_color rayray::single_sphere_tracer::trace_ray(const ray& ray) const
{
//	shade_rec sr(*scene_ptr_);
//	double t;
//	if (scene_ptr_->sphere_.hit(ray, t, sr))
//	{
//		return rayray::red();
//	}

    // NOTHING TO DO
	return rayray::black();
}

rayray::rgb_color rayray::single_sphere_tracer::trace_ray(const ray& ray, const int& depth) const
{
	// NOTHING TO DO
	return rgb_color();
}

