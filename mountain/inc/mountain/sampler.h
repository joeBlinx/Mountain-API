//
// Created by stiven on 1/6/21.
//

#ifndef SANDBOX_SAMPLER_H
#define SANDBOX_SAMPLER_H

#include "context.h"
namespace mountain::image {
    struct sampler {
        /**
         * Create a basic sampler with mipmap
         * @param context: Vulkan context
         * @param mipmap_levels: mipmap level you want
         */
        sampler(Context const &context, uint32_t mipmap_levels);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
        explicit operator vk::Sampler() const{return *_sampler;}
#endif
    private:
        vk::UniqueSampler _sampler;
    };
}
#endif //SANDBOX_SAMPLER_H
