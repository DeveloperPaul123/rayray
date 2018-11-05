#include "raytracer/cameras/pinhole_camera.h"
#include "raytracer/samplers/sampler.h"
#include "raytracer/tracers/tracer.h"

#include <cassert>
#include <algorithm>

rayray::pinhole_camera::pinhole_camera()
    :camera(), d_(500), zoom_(1.0)
{
    
}

rayray::image<unsigned char> rayray::pinhole_camera::render_scene(const scene& scene)
{
    ray ray;
    const auto zw = 100.0;
    auto vp = scene.view_plane();
    int depth = 0;
    image<unsigned char> output(vp.horizontal_resolution(),
        vp.vertical_resolution());

    ray.set_origin({ eye_.x(), eye_.y(), eye_.z() });

    auto horz_res = vp.horizontal_resolution();
    auto vert_res = vp.vertical_resolution();
    auto gamma = vp.gamma();
    assert(vp.sampler());

    const auto samples = vp.sampler()->number_samples();
    auto n = static_cast<int>(sqrt(static_cast<float>(samples)));

    auto pixel_size = vp.pixel_size() / zoom();

    for (auto r = 0; r < vp.vertical_resolution(); r++)
    {
        for (auto c = 0; c < vp.horizontal_resolution(); c++)
        {
            // default color is the background color
            auto color = scene.background_color();

            // iterate through all the samples.
            for (auto p = 0; p < n; p++)
            {
                for(auto q = 0; q < n; q++)
                {
                    point<double> pp = { pixel_size* (c - 0.5 * vp.horizontal_resolution() + (q + 0.5) / n), 
                        pixel_size * (r - 0.5 * vp.vertical_resolution() + (p + 0.5) / n) };
                    ray.set_direction(get_direction(pp));
                    color += scene.tracer_ptr()->trace_ray(ray, depth);
                }
            }

            color /= static_cast<double>(samples);
            color *= exposure_time;

            // clamp colors to 1
            auto max_color = *std::max_element(color.begin(), color.end());
            color /= max_color;
            
            output.set(r, c, 0, color.red() * 255);
            output.set(r, c, 1, color.green() * 255);
            output.set(r, c, 2, color.blue() * 255);
        }
    }
    return output;
}

void rayray::pinhole_camera::set_zoom(const double& z)
{
    zoom_ = z;
}

double rayray::pinhole_camera::zoom() const
{
    return zoom_;
}

void rayray::pinhole_camera::set_view_plane_distance(const double& d)
{
    d_ = d;
}

double rayray::pinhole_camera::view_plane_distance() const
{
    return d_;
}

rayray::vector<double, 3> rayray::pinhole_camera::get_direction(const point<double>& point)
{
    auto result = point.x() * u + point.y() * v - d_ * w;
    vector<double, 3> dir({ result[0], result[1], result[2] });

    return dir.to_unit_vector();
}

