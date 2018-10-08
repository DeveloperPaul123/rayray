#include "raytracer/core/scene.h"
#include "raytracer/tracers/single_sphere_tracer.h"
#include "raytracer/image/image_io.h"
#include "raytracer/core/shade_rec.h"

rayray::scene::scene() : sphere_({ 0.0, 0.0, 0.0 }, 0.0), view_plane_(200, 200, 1.0, 1.0)
{
    sphere_.set_center({ 0.0, 0.0,0.0 });
    sphere_.set_radius(85.0);
}

rayray::scene::~scene()
{
}

//rayray::image<unsigned char> rayray::scene::render()
//{
//    ray ray;
//    const auto zw = 100.0;
//    image<unsigned char> output_image(view_plane_.horizontal_resolution(), view_plane_.vertical_resolution());
//
//    ray.set_direction({ 0.0, 0.0, -1.0 });
//
//    auto pixel_size = view_plane_.pixel_size();
//    auto horz_res = view_plane_.horizontal_resolution();
//    auto vert_res = view_plane_.vertical_resolution();
//    auto gamma = view_plane_.gamma();
//    for(auto r = 0; r < view_plane_.vertical_resolution(); r++)
//    {
//        for(auto c = 0; c < view_plane_.horizontal_resolution(); c++)
//        {
//            auto x = pixel_size * (c - 0.5 * (horz_res - 1.0));
//            auto y = pixel_size * (r - 0.5 * (vert_res - 1.0));
//            ray.set_origin({ x, y, zw });
//            auto color = tracer_ptr_->trace_ray(ray);
//            // gamma correction
//            if(gamma != 1.0)
//            {
//                color = color ^ view_plane_.inverse_gamma();
//            }
//            output_image.set(r, c, 0, color.red() * 255);
//            output_image.set(r, c, 1, color.green() * 255);
//            output_image.set(r, c, 2, color.blue() * 255);
//        }
//    }
//
//    return output_image;
//}

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
