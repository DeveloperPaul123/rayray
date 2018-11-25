#pragma once
#include "raytracer/lights/light.h"

namespace rayray
{
    class point_light : public light
    {
    public:
        point_light();
        void set_location(const vector<double, 3>& location);
        vector<double, 3> location() const;
        void set_color(const rgb_color &color);
        rgb_color color() const;
        vector<double, 3> get_direction(shade_rec& shade_rec) override;
        rgb_color radiance(shade_rec& shade_rec) override;
        void set_radiance_scaling(const double& scaling);
        double radiance_scaling() const;
    private:
        double radiance_scaling_;
        rgb_color color_;
        vector<double, 3> location_;
    };
}
