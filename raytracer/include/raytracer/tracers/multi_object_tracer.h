#pragma once

#include "tracer.h"

namespace rayray
{

    class multi_object_tracer : public tracer
    {
    public:
        multi_object_tracer();
        multi_object_tracer(scene* scene_ptr);
        rgb_color trace_ray(const rayray::ray& ray) const override;
        rgb_color trace_ray(const rayray::ray& ray, const int& depth) const override;
    };
}
