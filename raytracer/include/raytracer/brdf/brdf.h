#pragma once
#include "raytracer/core/vector.h"
#include "raytracer/samplers/sampler.h"
#include "raytracer/core/shade_rec.h"
#include "raytracer/core/rgb_color.h"

namespace rayray
{
    /**
     * @brief Class that encapsulates a bidirectional reflectance distribution function
     * @details At a high level, this class (function) decribes how light reflects at surfaces.
     */
    class brdf
    {
    protected:
        vector<double, 3> normal_;
        sampler* sampler_ptr_;

    public:
        virtual ~brdf() = default;

        void set_normal(const vector<double, 3> & normal)
        {
            normal_ = normal;
        }

        vector<double, 3> normal() const
        {
            return normal_;
        }
        void set_sampler(sampler* sampler)
        {
            sampler_ptr_ = sampler;
        }

        sampler* sampler() const
        {
            return sampler_ptr_;
        }

        virtual rgb_color f(const shade_rec & sr, const vector<double, 3> &wi, const vector<double, 3> &wo) = 0;
        virtual rgb_color sample_f(const shade_rec& sr, vector<double, 3> &wi, vector<double, 3> &wo) = 0;
        virtual rgb_color rho(const shade_rec &sr, const vector<double, 3> &wo) = 0;
    };
}