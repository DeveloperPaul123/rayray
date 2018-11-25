#pragma once

#include "raytracer/materials/material.h"
#include "raytracer/brdf/lambertian.h"

namespace rayray
{
    class matte : public material
    {
    public:
        matte();
        void set_ka(const double k);
        void set_kd(const double k);
        void set_cd(const rgb_color c);
        void set_cd(const double r, const double g, const double b);
        void set_cd(const double c);
        virtual rgb_color shade(shade_rec& sr);

        rgb_color area_light_shade(shade_rec& sr) override;
        rgb_color path_shade(shade_rec& sr) override;
    private:
        lambertian ambient_brdf_;
        lambertian diffuse_brdf_;
    };
}
