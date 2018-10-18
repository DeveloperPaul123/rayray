#include "raytracer/samplers/jittered_sampler.h"
#include "raytracer/utilities/math.h"

rayray::jittered_sampler::jittered_sampler(const int num_samples)
    : sampler(num_samples)
{
}

void rayray::jittered_sampler::generate_samples()
{
    auto n = static_cast<int>(std::sqrt(float(number_samples())));
    for (auto p = 0; p < number_sets_; p++) 
    {
        for (auto j = 0; j < n; j++)
        {
            for (auto k = 0; k < n; k++)
            {
                point<double, 2> sp({ (k + utilties::math::rand_float()) / n,
                    (j + utilties::math::rand_float()) / n });
                samples_.push_back(sp);
            }
        }
    }
}
