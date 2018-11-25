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

void rayray::scene::set_tracer(rayray::tracer* t)
{
    tracer_ = t;
}

rayray::tracer* rayray::scene::tracer_ptr() const
{
    return tracer_;
}

void rayray::scene::set_ambient_light(ambient_light* light)
{
    ambient_ptr_ = light;
}

rayray::ambient_light* rayray::scene::ambient_light_ptr() const
{
    return ambient_ptr_;
}

void rayray::scene::add_object(rayray::geometric_object* object)
{
    hit_objects_.push_back(object);
}

std::vector<rayray::geometric_object*> rayray::scene::objects() const
{
    return hit_objects_;
}

void rayray::scene::add_light(light* light)
{
    lights_.push_back(light);
}

void rayray::scene::set_lights(const std::vector<light*>& lights)
{
    lights_ = lights;
}

std::vector<rayray::light*> rayray::scene::lights() const
{
    return lights_;
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

rayray::shade_rec rayray::scene::hit_objects(const ray& ray)
{
    shade_rec shade_rec(*this);
    double t;
    auto t_min = 1000000000000000000.0;
    auto num_objects = hit_objects_.size();
    vector<double, 3> normal;
    point<double, 3> local_hit_point;
    material* mat_ptr{nullptr};
    for(auto &object : hit_objects_)
    {
        if(object->hit(ray, t, shade_rec) && t < t_min)
        {
            shade_rec.hit_object = true;
            t_min = t;
            shade_rec.color = object->color();
            local_hit_point = ray.origin() + t * ray.direction();
            normal = shade_rec.normal;
            mat_ptr = object->material_ptr();
        }
    }

    if(shade_rec.hit_object)
    {
        shade_rec.t = t_min;
        shade_rec.normal = normal;
        shade_rec.local_hit_point = local_hit_point;
        shade_rec.material_ptr = mat_ptr;
    }

    return shade_rec;
}
