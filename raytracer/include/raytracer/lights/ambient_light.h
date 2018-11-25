#pragma once
#include "raytracer/lights/light.h"

namespace rayray
{
    class ambient_light : public light
    {
    public:
        ambient_light();
        ambient_light(const rgb_color &color, const double &ls);
        void set_color(const rgb_color& color);
        rgb_color color() const;
        void set_radiance_scaling(const double& ls);
        double radiance_scaling() const;
        vector<double, 3> get_direction(shade_rec& shade_rec) override;
        rgb_color radiance(shade_rec& shade_rec) override;
    private:
        double radiance_scaling_;
        rgb_color color_;
    };
}
