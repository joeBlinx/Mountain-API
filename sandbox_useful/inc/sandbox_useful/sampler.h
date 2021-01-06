//
// Created by stiven on 1/6/21.
//

#ifndef SANDBOX_SAMPLER_H
#define SANDBOX_SAMPLER_H

#include "context.hpp"

struct sampler{
    sampler(Context const& context);
private:
    vk::UniqueSampler _sampler;
};
#endif //SANDBOX_SAMPLER_H
