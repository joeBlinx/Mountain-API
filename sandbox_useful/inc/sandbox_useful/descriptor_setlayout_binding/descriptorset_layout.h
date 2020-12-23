//
// Created by stiven on 12/23/20.
//

#ifndef SANDBOX_DESCRIPTORSET_LAYOUT_H
#define SANDBOX_DESCRIPTORSET_LAYOUT_H
#include <vulkan/vulkan.hpp>
#include "sandbox_useful/context.hpp"
namespace descriptorset_layout {
    vk::DescriptorSetLayoutBinding create_descriptor_uniform(int binding, vk::ShaderStageFlags const &shader);
    vk::DescriptorSetLayout create_descriptorset_layout(Context const& context, std::vector<vk::DescriptorSetLayoutBinding> && set_layout_bindings);
}
#endif //SANDBOX_DESCRIPTORSET_LAYOUT_H
