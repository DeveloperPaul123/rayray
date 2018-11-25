#include "raytracer/lights/point_light.h"
#include "raytracer/core/shade_rec.h"

rayray::point_light::point_light()
    : light(), radiance_scaling_(1.0), color_(1.0, 1.0, 1.0), location_({ 0.0, 0.0, 0.0 })
{
}

void rayray::point_light::set_location(const vector<double, 3>& location)
{
    location_ = location;
}

rayray::vector<double, 3> rayray::point_light::location() const
{
    return location_;
}

void rayray::point_light::set_color(const rgb_color& color)
{
    color_ = color;
}

rayray::rgb_color rayray::point_light::color() const
{
    return color_;
}

rayray::vector<double, 3> rayray::point_light::get_direction(shade_rec& shade_rec)
{
    return (location_ - shade_rec.local_hit_point).to_unit_vector();
}

rayray::rgb_color rayray::point_light::radiance(shade_rec& shade_rec)
{
    return radiance_scaling_ * color_;
}

void rayray::point_light::set_radiance_scaling(const double& scaling)
{
    radiance_scaling_ = scaling;
}

double rayray::point_light::radiance_scaling() const
{
    return radiance_scaling_;
}

