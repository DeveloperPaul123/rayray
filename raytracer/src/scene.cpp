#include "raytracer/core/scene.h"
#include "raytracer/tracers/single_sphere_tracer.h"
#include "raytracer/image/image_io.h"
#include "raytracer/core/shade_rec.h"

rayray::scene::scene() : view_plane_(200, 200, 1.0, 1.0)
{
}

rayray::scene::~scene()
{
}

void rayray::scene::add_object(rayray::geometric_object* object)
{
    hit_objects_.push_back(object);
}

std::vector<rayray::geometric_object*> rayray::scene::objects() const
{
    return hit_objects_;
}

const rayray::view_plane& rayray::scene::view_plane() const
{
    return view_plane_;
}

void rayray::scene::set_view_plane(const rayray::view_plane& view_plane)
{
    view_plane_ = view_plane;
}

const rayray::rgb_color& rayray::scene::background_color() const
{
    return background_color_;
}

void rayray::scene::set_background_color(const rgb_color& background_color)
{
    background_color_ = background_color;
}

rayray::shade_rec rayray::scene::hit_bare_bones_objects(const ray& ray)
{
    shade_rec shade_rec(*this);
    double t;
    double t_min = 1000000000000000000.0;
    auto num_objects = hit_objects_.size();
    for(auto &object : hit_objects_)
    {
        if(object->hit(ray, t, shade_rec) && t < t_min)
        {
            shade_rec.hit_object = true;
            t_min = t;
            shade_rec.color = object->color();
        }
    }

    return shade_rec;
}
