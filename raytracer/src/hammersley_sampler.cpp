#include "raytracer/samplers/hammersley_sampler.h"

double phi(int j)
{
    auto x = 0.0; 
    auto f = 0.5;
    while (j)
    {
        x += f * static_cast<double>(!j & 1); 
        j /= 2; 
        f *= 0.5;
    } 
    return (x);
}

rayray::hammersley_sampler::hammersley_sampler()
{
}

rayray::hammersley_sampler::hammersley_sampler(const int& num_samples)
{
}

rayray::hammersley_sampler::hammersley_sampler(const int& num_samples, const int& num_sets)
{
}

void rayray::hammersley_sampler::generate_samples()
{
    for (int p = 0; p < number_sets_; p++)
        for (int j = 0; j < number_samples_; j++) {
            point<double> pv(static_cast<double>(j) / static_cast<double>(number_samples_), phi(j));
            samples_.emplace_back(pv);
        }
}
