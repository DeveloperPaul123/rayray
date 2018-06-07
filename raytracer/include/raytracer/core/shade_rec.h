#pragma once
#include "raytracer/core/point.h"
#include "raytracer/core/scene.h"

namespace rayray
{
	class shade_rec
	{
	public:
		
		bool hit_object = false;
		point<double, 3> local_hit_point;
		scene& scene_ref;
		vector<double, 3> normal;

		shade_rec(scene& scene);
	};
}
