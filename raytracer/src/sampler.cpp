#include "raytracer/samplers/sampler.h"
#include <algorithm>
#include <random>
#include "raytracer/utilities/math.h"
#include "raytracer/utilities/constants.h"

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

void rayray::sampler::map_samples_to_unit_disk()
{
    int size = samples_.size();
    float r, phi;		// polar coordinates
    point<double> sp; 		// sample point on unit disk

    disk_samples_.reserve(size);

    for (int j = 0; j < size; j++) {
        // map sample point to [-1, 1] X [-1,1]

        sp[0] = 2.0 * samples_[j].x() - 1.0;
        sp[1] = 2.0 * samples_[j].y() - 1.0;

        if (sp.x() > -sp.y()) {			// sectors 1 and 2
            if (sp.x() > sp.y()) {		// sector 1
                r = sp.x();
                phi = sp.y() / sp.x();
            }
            else {					// sector 2
                r = sp.y();
                phi = 2 - sp.x() / sp.y();
            }
        }
        else {						// sectors 3 and 4
            if (sp.x() < sp.y()) {		// sector 3
                r = -sp.x();
                phi = 4 + sp.y() / sp.x();
            }
            else {					// sector 4
                r = -sp.y();
                if (sp.y() != 0.0)	// avoid division by zero at origin
                    phi = 6 - sp.x() / sp.y();
                else
                    phi = 0.0;
            }
        }

        phi *= PI / 4.0;

        disk_samples_[j][0] = r * cos(phi);
        disk_samples_[j][1] = r * sin(phi);
    }
}

void rayray::sampler::map_samples_to_hemisphere(const double e)
{
    int size = samples_.size();
    hemisphere_samples_.reserve(number_samples() * number_sets());

    for (auto j = 0; j < size; j++) {
        auto cos_phi = cos(2.0 * PI * samples_[j].x());
        auto sin_phi = sin(2.0 * PI * samples_[j].x());
        auto cos_theta = pow((1.0 - samples_[j].y()), 1.0 / (e + 1.0));
        auto sin_theta = sqrt(1.0 - cos_theta * cos_theta);
        auto pu = sin_theta * cos_phi;
        auto pv = sin_theta * sin_phi;
        auto pw = cos_theta;
        hemisphere_samples_.push_back({ pu, pv, pw });
    }
}
