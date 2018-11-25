#pragma once
#include "raytracer/tracers/tracer.h"

namespace rayray
{
    class ray_cast_tracer : public tracer
    {
    public:
        ray_cast_tracer();
        ray_cast_tracer(scene * scene_ptr);
        rgb_color trace_ray(const rayray::ray& ray) const override;
        rgb_color trace_ray(const rayray::ray& ray, const int& depth) const override;
        rgb_color trace_ray(const rayray::ray& ray, float& t_min, const int& depth) override;
    };
}
