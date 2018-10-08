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
        void set_scene(scene* scene_ptr);
		virtual rgb_color trace_ray(const rayray::ray& ray) const = 0;
		virtual rgb_color trace_ray(const rayray::ray& ray, const int &depth) const = 0;
	protected:
        scene * scene_ptr_{ nullptr };
	};
}
