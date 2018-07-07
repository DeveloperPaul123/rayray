#pragma once
#include "raytracer/core/rgb_color.h"
#include "raytracer/core/ray.h"

namespace rayray
{
	class scene;

	class tracer
	{
	public:
		tracer();
		tracer(scene* scene_ptr);
		virtual ~tracer() = default;

		virtual rgb_color trace_ray(const ray& ray) const = 0;
		virtual rgb_color trace_ray(const ray& ray, const int &depth) const = 0;
	protected:
		scene * scene_ptr_ = nullptr;
	};
}
