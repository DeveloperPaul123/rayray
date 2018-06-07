#pragma once
#include <vector>
#include "raytracer/geometry/geometric_object.h"

namespace rayray
{
	class scene
	{
	public:
		scene();
	private:
		std::vector<rayray::geometric_object*> hit_objects_;
	};
}
