#include "raytracer/tracers/ray_cast_tracer.h"
#include "raytracer/core/shade_rec.h"

rayray::ray_cast_tracer::ray_cast_tracer()
    : tracer()
{
    
}

rayray::ray_cast_tracer::ray_cast_tracer(scene* scene_ptr)
    : tracer(scene_ptr)
{
    
}

rayray::rgb_color rayray::ray_cast_tracer::trace_ray(const rayray::ray& ray) const
{
    return black();
}

rayray::rgb_color rayray::ray_cast_tracer::trace_ray(const rayray::ray& ray, const int& depth) const
{
    shade_rec sr(scene_ptr_->hit_objects(ray));

    if(sr.hit_object)
    {
        sr.ray = ray;
        return sr.material_ptr->shade(sr);
    }

    return scene_ptr_->background_color();
}

rayray::rgb_color rayray::ray_cast_tracer::trace_ray(const rayray::ray& ray, float& t_min, const int& depth)
{
    return black();
}




