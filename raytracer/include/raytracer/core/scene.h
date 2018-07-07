#pragma once
#include <vector>
#include "raytracer/geometry/geometric_object.h"
#include "rgb_color.h"
#include "raytracer/geometry/sphere.h"

namespace rayray
{
	class tracer;

	class scene
	{
	public:
		sphere sphere_;
		scene();
	private:
		rgb_color background_color_;
		tracer * tracer_ptr_;
		std::vector<rayray::geometric_object*> hit_objects_;
	};
}
