//
// Created by stiven on 1/6/21.
//

#ifndef SANDBOX_SAMPLER_H
#define SANDBOX_SAMPLER_H

#include "context.h"
namespace mountain::image {
    struct sampler {
        sampler(Context const &context, uint32_t mipmap_levels);
        operator vk::Sampler() const{return *_sampler;}
    private:
        vk::UniqueSampler _sampler;
    };
}
#endif //SANDBOX_SAMPLER_H
