#pragma once
#include "sampler.h"

namespace rayray
{
    class hammersley_sampler : public sampler
    {
    public:
        hammersley_sampler();
        explicit hammersley_sampler(const int &num_samples);
        hammersley_sampler(const int &num_samples, const int &num_sets);

        void generate_samples() override;
    };
}
