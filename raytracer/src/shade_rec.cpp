#include "raytracer/core/shade_rec.h"

rayray::shade_rec::shade_rec(scene& scene)
	: hit_object(false), local_hit_point(), scene_ref(scene)
{
	
}
