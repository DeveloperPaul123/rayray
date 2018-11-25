#pragma once
#include "raytracer/core/vector.h"
#include "raytracer/core/rgb_color.h"

namespace rayray
{
    class shade_rec;

    class light
    {
    public:
        virtual ~light() = default;
        virtual vector<double, 3> get_direction(shade_rec &shade_rec) = 0;
        virtual rgb_color radiance(shade_rec &shade_rec) = 0;

    protected:
        bool shadows_{ false };
    };
}
