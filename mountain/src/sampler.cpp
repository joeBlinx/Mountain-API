//
// Created by stiven on 1/6/21.
//

#include "../public_inc/mountain/sampler.h"
namespace mountain {

    image::sampler::sampler(Context const &context, uint32_t mipmap_levels) {
        //TODO: basic sampler but i need to find a way to be more flexible
        // Linear filter and repeat image
        vk::SamplerCreateInfo sampler_info{};
        sampler_info.magFilter = vk::Filter::eLinear;
        sampler_info.minFilter = vk::Filter::eLinear;

        sampler_info.addressModeU = vk::SamplerAddressMode::eRepeat;
        sampler_info.addressModeV = vk::SamplerAddressMode::eRepeat;
        sampler_info.addressModeW = vk::SamplerAddressMode::eRepeat;

        sampler_info.anisotropyEnable = VK_TRUE;

        vk::PhysicalDeviceProperties properties{};
        context.get_physical_device().getProperties(&properties);
        sampler_info.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
        //we go for maximum quality
        sampler_info.borderColor = vk::BorderColor::eIntOpaqueBlack;
        sampler_info.unnormalizedCoordinates = VK_FALSE;

        sampler_info.compareEnable = VK_FALSE;
        sampler_info.compareOp = vk::CompareOp::eAlways;

        sampler_info.mipmapMode = vk::SamplerMipmapMode::eLinear;
        sampler_info.mipLodBias = 0.f;
        sampler_info.minLod = 0.f;
        sampler_info.maxLod = mipmap_levels;

        _sampler = context->createSamplerUnique(sampler_info);
    }
}

