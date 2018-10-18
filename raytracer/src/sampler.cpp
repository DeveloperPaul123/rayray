#include "raytracer/samplers/sampler.h"
#include <algorithm>
#include <random>
#include "raytracer/utilities/math.h"

namespace std {
    class random_device;
}

rayray::sampler::sampler()
    :number_samples_(1), number_sets_(83)
{
    init_data();
}

rayray::sampler::sampler(const int& num_samples)
    :number_samples_(num_samples), number_sets_(83)
{
    init_data();
}

rayray::sampler::sampler(const int& num_samples, const int& num_sets)
    :number_samples_(num_samples), number_sets_(num_sets)
{
    init_data();
}

void rayray::sampler::init_data()
{
    samples_.reserve(number_samples_ * number_sets_);
    setup_shuffled_indices();
}

rayray::sampler::~sampler()
{
}

const int& rayray::sampler::number_samples() const
{
    return number_samples_;
}

void rayray::sampler::set_number_samples(const int number_samples)
{
    number_samples_ = number_samples;
}

const int& rayray::sampler::number_sets() const
{
    return number_sets_;
}

void rayray::sampler::set_number_sets(const int number_sets)
{
    number_sets_ = number_sets;
}

const std::vector<rayray::point<double, 2>>& rayray::sampler::samples() const
{
    return samples_;
}

const std::vector<int>& rayray::sampler::shuffled_indices() const
{
    return shuffled_indices_;
}

const unsigned long& rayray::sampler::count() const
{
    return count_;
}

const int& rayray::sampler::jump() const
{
    return jump_;
}

void rayray::sampler::setup_shuffled_indices()
{
    shuffled_indices_.reserve(number_samples_ * number_sets_);
    std::vector<int> indices;

    for (int j = 0; j < number_samples_; j++)
        indices.push_back(j);

    std::random_device rng;
    std::mt19937 urng(rng());
    for (int p = 0; p < number_sets_; p++) {

        std::shuffle(indices.begin(), indices.end(), urng);

        for (int j = 0; j < number_samples_; j++)
            shuffled_indices_.push_back(indices[j]);
    }
}

void rayray::sampler::shuffle_samples()
{
    // TODO
}

rayray::point<double, 2> rayray::sampler::sample_unit_square()
{ 
    // start of a new pixel
    if (count_ % number_samples_ == 0) 
    {
        // random index jump initialised to zero in constructor
        jump_ = (utilties::math::rand_int() % number_sets_) * number_samples_;
    }

    return (samples_[jump_ + shuffled_indices_[jump_ + count_++ % number_samples_]]);
}
