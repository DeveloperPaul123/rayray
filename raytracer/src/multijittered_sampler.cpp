#include "raytracer/samplers/multijittered_sampler.h"
#include "raytracer/utilities/math.h"

rayray::multijittered_sampler::multijittered_sampler()
    :sampler()
{
    
}

rayray::multijittered_sampler::multijittered_sampler(const int& num_samples)
    :sampler(num_samples)
{
    
}

rayray::multijittered_sampler::multijittered_sampler(const int& num_samples, const int& num_sets)
    :sampler(num_samples, num_sets)
{
    
}

void rayray::multijittered_sampler::generate_samples()
{
    auto n = static_cast<int>(sqrt(static_cast<float>(number_samples())));
    auto subcell_width = 1.0 / static_cast<double>(number_samples());

    // fill the samples array with dummy points to allow us to use the [ ] notation when we set the 
    // initial patterns
    point<double> fill_point;
    for (int j = 0; j < number_samples() * number_sets(); j++)
        samples_.push_back(fill_point);

    // distribute points in the initial patterns
    for (int p = 0; p < number_sets(); p++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                samples_[i * n + j + p * number_samples()][0] = (i * n + j) * subcell_width + utilties::math::rand_float(0, subcell_width);
                samples_[i * n + j + p * number_samples()][1] = (j * n + i) * subcell_width + utilties::math::rand_float(0, subcell_width);
            }

    // shuffle x coordinates
    for (int p = 0; p < number_sets(); p++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                int k = utilties::math::rand_int(j, n - 1);
                auto t = samples_[i * n + j + p * number_samples()].x();
                // [0] is x
                samples_[i * n + j + p * number_samples()][0] = samples_[i * n + k + p * number_samples()].x();
                samples_[i * n + k + p * number_samples()][0] = t;
            }

    // shuffle y coordinates
    for (int p = 0; p < number_sets(); p++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                int k = utilties::math::rand_int(j, n - 1);
                float t = samples_[j * n + i + p * number_samples()].y();
                // [1] is y
                samples_[j * n + i + p * number_samples()][1] = samples_[k * n + i + p * number_samples()].y();
                samples_[k * n + i + p * number_samples()][1] = t;
            }
}


