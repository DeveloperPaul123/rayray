#include "raytracer/samplers/nrooks_sampler.h"
#include "raytracer/utilities/math.h"

rayray::nrooks_sampler::nrooks_sampler()
    : sampler()
{
    
}

rayray::nrooks_sampler::nrooks_sampler(const int& num_samples)
    :sampler(num_samples)
{
    
}

rayray::nrooks_sampler::nrooks_sampler(const int& num_samples, const int& num_sets)
    : sampler(num_samples, num_sets)
{
    
}

void rayray::nrooks_sampler::generate_samples()
{
    for (int p = 0; p < number_sets_; p++)
        for (int j = 0; j < number_samples_; j++) {
            point<double> sp((j + utilties::math::rand_float()) / number_samples_, 
                (j + utilties::math::rand_float()) / number_samples_);
            samples_.emplace_back(sp);
        }

    shuffle_x_coordinates();
    shuffle_y_coordinates();
}

void rayray::nrooks_sampler::shuffle_x_coordinates()
{
    for (auto p = 0; p < number_sets_; p++)
    {
        for (auto i = 0; i < number_samples_ - 1; i++)
        {
            // find the target
            auto target = utilties::math::rand_int() % number_samples_ + p * number_samples_;
            // swap the current sample with the target sample
            auto temp = samples_[i + p * number_samples_ + 1].x();
            samples_[i + p * number_samples_ + 1][0] = samples_[target].x();
            samples_[target][0]= temp;
        }
    } 
}

void rayray::nrooks_sampler::shuffle_y_coordinates()
{
    for (auto p = 0; p < number_sets_; p++)
    {
        for (auto i = 0; i < number_samples_ - 1; i++)
        {
            // find the target
            auto target = utilties::math::rand_int() % number_samples_ + p * number_samples_;
            // swap the current sample with the target sample
            auto temp = samples_[i + p * number_samples_ + 1].y();
            samples_[i + p * number_samples_ + 1][1] = samples_[target].y();
            samples_[target][1] = temp;
        }
    }
}


