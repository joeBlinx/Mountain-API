//
// Created by stiven on 12/23/20.
//
#include "mountain/context.h"
#include "mountain/descriptorset_layout.h"
#include "utils/log.hpp"
namespace mountain::descriptorset_layout {
    vk::DescriptorSetLayoutBinding create_descriptor_image_sampler(int binding, vk::ShaderStageFlags const &shader){
        vk::DescriptorSetLayoutBinding image_layout{};
        image_layout.binding = binding;
        image_layout.descriptorType = vk::DescriptorType::eCombinedImageSampler;
        image_layout.pImmutableSamplers = nullptr;
        image_layout.descriptorCount = 1; // can be greater than 1 if we use uniform arrays
        image_layout.stageFlags = shader;
        return image_layout;
    }
    vk::DescriptorSetLayoutBinding create_descriptor_uniform(int binding, vk::ShaderStageFlags const &shader) {
        vk::DescriptorSetLayoutBinding ubo_binding_layout{};
        ubo_binding_layout.binding = binding;
        ubo_binding_layout.descriptorType = vk::DescriptorType::eUniformBuffer;
        ubo_binding_layout.descriptorCount = 1; // can be greater than 1 if we use uniform arrays
        ubo_binding_layout.stageFlags = shader;
        return ubo_binding_layout;

    }
    vk::DescriptorSetLayout create_descriptorset_layout(Context const& context,
                                                        std::vector<vk::DescriptorSetLayoutBinding> && set_layout_bindings){
        vk::DescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{};
        descriptorSetLayoutCreateInfo.bindingCount = static_cast<uint32_t>(set_layout_bindings.size());
        descriptorSetLayoutCreateInfo.pBindings = set_layout_bindings.data();

        vk::DescriptorSetLayout descriptor_layout;
        checkError(context.get_device().createDescriptorSetLayout(&descriptorSetLayoutCreateInfo,
                                                       nullptr,
                                                       &descriptor_layout),
                   "unable to create Descriptor Set Layouts");
        return descriptor_layout;
    }

}