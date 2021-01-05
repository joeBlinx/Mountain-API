//
// Created by stiven on 12/23/20.
//
#include <context.hpp>
#include "descriptor_setlayout_binding/descriptorset_layout.h"
namespace descriptorset_layout {
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
        descriptorSetLayoutCreateInfo.bindingCount = set_layout_bindings.size();
        descriptorSetLayoutCreateInfo.pBindings = set_layout_bindings.data();

        vk::DescriptorSetLayout descriptor_layout;
        context.get_device().createDescriptorSetLayout(&descriptorSetLayoutCreateInfo,
                                                       nullptr,
                                                       &descriptor_layout);
        return descriptor_layout;
    }

}