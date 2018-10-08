#include "raytracer/tracers/multi_object_tracer.h"
#include "raytracer/core/scene.h"
#include "raytracer/core/shade_rec.h"

rayray::multi_object_tracer::multi_object_tracer()
    :tracer()
{
}

rayray::multi_object_tracer::multi_object_tracer(scene* scene_ptr)
    : tracer(scene_ptr)
{
    
}

rayray::rgb_color rayray::multi_object_tracer::trace_ray(const rayray::ray & ray) const
{
    shade_rec sr(scene_ptr_->hit_bare_bones_objects(ray));
    if(sr.hit_object)
    {
        return sr.color;
    }
    return scene_ptr_->background_color();
}

rayray::rgb_color rayray::multi_object_tracer::trace_ray(const rayray::ray& ray, const int& depth) const
{
    return trace_ray(ray);
}

