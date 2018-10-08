#pragma once
#include "scene.h"
#include "raytracer/tracers/tracer.h"
#include <cassert>

namespace rayray
{
    class scene_renderer
    {
        scene* scene_{nullptr};
        tracer* tracer_{ nullptr };
    public:
        scene_renderer(scene* scene, tracer* tracer);
        template<typename ImageType>
        image<ImageType> render()
        {
            assert(scene_ != nullptr);
            assert(tracer_ != nullptr);

            ray ray;
            const auto zw = 100.0;
            auto vp = scene_->view_plane();
            image<ImageType> output(vp.horizontal_resolution(),
                vp.vertical_resolution());

            ray.set_direction({ 0.0, 0.0, -1.0 });

            auto pixel_size = vp.pixel_size();
            auto horz_res = vp.horizontal_resolution();
            auto vert_res = vp.vertical_resolution();
            auto gamma = vp.gamma();
            for (auto r = 0; r < vp.vertical_resolution(); r++)
            {
                for (auto c = 0; c < vp.horizontal_resolution(); c++)
                {
                    auto x = pixel_size * (c - 0.5 * (horz_res - 1.0));
                    auto y = pixel_size * (r - 0.5 * (vert_res - 1.0));
                    ray.set_origin({ x, y, zw });
                    auto color = tracer_->trace_ray(ray);
                    // gamma correction
                    if (gamma != 1.0)
                    {
                        color = color ^ vp.inverse_gamma();
                    }
                    output.set(r, c, 0, color.red() * 255);
                    output.set(r, c, 1, color.green() * 255);
                    output.set(r, c, 2, color.blue() * 255);
                }
            }

            return output;
        }
    };
}
