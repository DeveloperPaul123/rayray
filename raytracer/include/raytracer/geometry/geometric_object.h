#pragma once
#include "raytracer/core/ray.h"

namespace rayray
{
	class shade_rec;

	class geometric_object
	{
	public:
		geometric_object() = default;
		virtual ~geometric_object() = default;
		virtual bool hit(const rayray::ray & ray, double &t_min, rayray::shade_rec &sr) const = 0;
	};
}
