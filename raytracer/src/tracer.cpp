#include <raytracer/tracers/tracer.h>

rayray::tracer::tracer()
{
	
}

rayray::tracer::tracer(scene* scene_ptr)
	: scene_ptr_(scene_ptr)
{
	
}

void rayray::tracer::set_scene(scene* scene_ptr)
{
    scene_ptr_ = scene_ptr;
}

