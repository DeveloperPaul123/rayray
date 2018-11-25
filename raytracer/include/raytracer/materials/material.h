#pragma once
#include "raytracer/core/rgb_color.h"

namespace rayray
{
    class shade_rec;

    class material
    {
    public:
        virtual ~material() = default;
        material() = default;
        virtual rgb_color shade(shade_rec &sr) = 0;
        virtual rgb_color area_light_shade(shade_rec &sr) = 0;
        virtual rgb_color path_shade(shade_rec &sr) = 0;
    };
}
