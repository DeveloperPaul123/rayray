#include "raytracer/materials/matte_material.h"
#include "raytracer/core/shade_rec.h"
#include "raytracer/lights/light.h"
#include <vector>
rayray::matte::matte()
    : material()
{
}

void rayray::matte::set_ka(const double k)
{
    ambient_brdf_.set_kd(k);
}

void rayray::matte::set_kd(const double k)
{
    diffuse_brdf_.set_kd(k);
}

void rayray::matte::set_cd(const rgb_color c)
{
    ambient_brdf_.set_cd(c);
    diffuse_brdf_.set_cd(c);
}

void rayray::matte::set_cd(const double c)
{
    ambient_brdf_.set_cd({ c, c, c });
    diffuse_brdf_.set_cd({ c, c, c });
}

void rayray::matte::set_cd(const double r, const double g, const double b)
{
    ambient_brdf_.set_cd({ r, g, b });
    diffuse_brdf_.set_cd({ r, g, b });
}

rayray::rgb_color rayray::matte::shade(shade_rec& sr)
{
    vector<double, 3> wo = -sr.ray.direction();
    rgb_color L = ambient_brdf_.rho(sr, wo) * sr.scene_ref.ambient_light_ptr()->radiance(sr);
    auto lights = sr.scene_ref.lights();
    auto num_lights = lights.size();
    for(auto j = 0; j < num_lights; j++)
    {
        auto wi = lights[j]->get_direction(sr);
        float ndotwi = rayray::dot(sr.normal, wi);

        if (ndotwi > 0.0)
        {
            L += diffuse_brdf_.f(sr, wo, wi) * lights[j]->radiance(sr) * ndotwi;
        }
    }

    return L;
}

rayray::rgb_color rayray::matte::area_light_shade(shade_rec& sr)
{
    return shade(sr);
}

rayray::rgb_color rayray::matte::path_shade(shade_rec& sr)
{
    return shade(sr);
}





