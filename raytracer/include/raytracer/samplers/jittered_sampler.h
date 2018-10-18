#pragma once
#include "sampler.h"

namespace rayray
{
    class jittered_sampler : public sampler
    {
    public:
        virtual ~jittered_sampler() = default;
        explicit jittered_sampler(const int num_samples);
        void generate_samples() override;
    };
}
