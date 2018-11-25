#pragma once
#include "tracer.h"

namespace rayray
{
	class single_sphere_tracer : public tracer
	{
	public:
		single_sphere_tracer();
		single_sphere_tracer(scene* scene_ptr);

		rgb_color trace_ray(const rayray::ray& ray) const override;
		rgb_color trace_ray(const rayray::ray& ray, const int& depth) const override;
	    rgb_color trace_ray(const rayray::ray& ray, float& t_min, const int& depth) override;
	};
}
