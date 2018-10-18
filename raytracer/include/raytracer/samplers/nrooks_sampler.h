#pragma once
#include "sampler.h"

namespace rayray
{
    class nrooks_sampler : public sampler
    {
    public:
        nrooks_sampler();
        explicit nrooks_sampler(const int &num_samples);
        nrooks_sampler(const int& num_samples, const int &num_sets);
        virtual ~nrooks_sampler() = default;

        void generate_samples() override;

    private:
        void shuffle_x_coordinates();
        void shuffle_y_coordinates();
    };
}
