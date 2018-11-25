#include "raytracer/lights/ambient_light.h"
#include "raytracer/core/shade_rec.h"

rayray::ambient_light::ambient_light()
    :radiance_scaling_(1.0), color_(rayray::black())
{
}

rayray::ambient_light::ambient_light(const rgb_color& color, const double& ls)
    :radiance_scaling_(ls), color_(color)
{
}

void rayray::ambient_light::set_color(const rgb_color& color)
{
    color_ = color;
}

rayray::rgb_color rayray::ambient_light::color() const
{
    return color_;
}

void rayray::ambient_light::set_radiance_scaling(const double& ls)
{
    radiance_scaling_ = ls;
}

double rayray::ambient_light::radiance_scaling() const
{
    return radiance_scaling_;
}

rayray::vector<double, 3> rayray::ambient_light::get_direction(shade_rec& shade_rec)
{
    return { 0.0, 0.0, 0.0 };
}

rayray::rgb_color rayray::ambient_light::radiance(shade_rec& shade_rec)
{
    auto result = color_ * radiance_scaling_;
    return { result[0], result[1], result[2] };
}
