#pragma once
#include <vector>
#include "raytracer/core/point.h"

namespace rayray
{
    class sampler
    {
    private:
        void init_data();
    protected:
        ~sampler();
        int number_samples_{ 0 };
        int number_sets_{ 0 };
        std::vector<point<double, 2>> samples_;
        std::vector<int> shuffled_indices_;
        unsigned long count_{0};
        int jump_{0};

    public:
        sampler();
        explicit sampler(const int &num_samples);
        sampler(const int &num_samples, const int &num_sets);

        const int& number_samples() const;
        void set_number_samples(const int number_samples);
        const int& number_sets() const;
        void set_number_sets(const int number_sets);

        const std::vector<point<double, 2>>& samples() const;
        const std::vector<int>& shuffled_indices() const;
        const unsigned long& count() const;
        const int& jump() const;

        virtual void generate_samples() = 0;
        void setup_shuffled_indices();
        void shuffle_samples();
        point<double, 2> sample_unit_square();
    };
}
