#pragma once
#include "raytracer/core/point.h"
#include "raytracer/core/scene.h"
#include "raytracer/materials/material.h"

namespace rayray
{
	class shade_rec
	{
	public:
		
		bool hit_object = false;
        point<double, 3> hit_point;
		point<double, 3> local_hit_point;
		scene& scene_ref;
		vector<double, 3> normal;
        rgb_color color;
        double t;
        ray ray;
        int depth;
        vector<double, 3> direction;
        material* material_ptr{ nullptr };
		shade_rec(scene& scene);
	};
}
