#include "raytracer/brdf/lambertian.h"
#include "raytracer/utilities/constants.h"

rayray::lambertian::lambertian()
{
    
}

double rayray::lambertian::kd() const
{
    return kd_;
}

rayray::rgb_color rayray::lambertian::cd() const
{
    return cd_;
}

void rayray::lambertian::set_kd(const double& kd)
{
    kd_ = kd;
}

void rayray::lambertian::set_cd(const rgb_color& color)
{
    cd_ = color;
}

rayray::rgb_color rayray::lambertian::f(const shade_rec& sr, const vector<double, 3>& wi, const vector<double, 3>& wo)
{
    auto result =  cd_ * kd_ * INVERSE_PI;
    return {result[0], result[1], result[2]};
}

rayray::rgb_color rayray::lambertian::sample_f(const shade_rec& sr, vector<double, 3>& wi, vector<double, 3>& wo)
{
    return rayray::black();
}

rayray::rgb_color rayray::lambertian::rho(const shade_rec& sr, const vector<double, 3>& wo)
{
    auto result = cd_ * kd_;
    return rgb_color{ result[0], result[1], result[2] };
}
