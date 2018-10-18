#pragma once
#include "sampler.h"

namespace rayray 
{
    class multijittered_sampler: public sampler
    {
    public:
        multijittered_sampler();
        multijittered_sampler(const int &num_samples);
        multijittered_sampler(const int &num_samples, const int &num_sets);

        void generate_samples() override;
    };
}
