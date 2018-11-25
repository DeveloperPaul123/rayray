#pragma once
#include "raytracer/brdf/brdf.h"

namespace rayray
{
    class lambertian : public brdf
    {
    private:
        double kd_;
        rgb_color cd_;
    public:
        lambertian();
        double kd() const;
        rgb_color cd() const;
        void set_kd(const double& kd);
        void set_cd(const rgb_color &color);
        rgb_color f(const shade_rec& sr, const vector<double, 3>& wi, const vector<double, 3>& wo) override;
        rgb_color sample_f(const shade_rec& sr, vector<double, 3>& wi, vector<double, 3>& wo) override;
        rgb_color rho(const shade_rec& sr, const vector<double, 3>& wo) override;
    };
}
