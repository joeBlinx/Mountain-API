//
// Created by stiven on 12/23/20.
//

#ifndef MOUNTAIN_API_DESCRIPTORSET_LAYOUT_H
#define MOUNTAIN_API_DESCRIPTORSET_LAYOUT_H
#include <vulkan/vulkan.hpp>
#include "context.h"
namespace mountain::descriptorset_layout {
        /**
         * Create descriptor layout to be use as a uniform
         * @param binding: number inside shader
         * @param shader: The stage of the shader this descriptor will be use
         * @return Corresponding descriptor set layout binding
         */
        vk::DescriptorSetLayoutBinding create_descriptor_uniform(int binding, vk::ShaderStageFlags const &shader);
        /**
         * Create descriptor layout to be use for image sampler
         * @param binding: number inside shader
         * @param shader: The stage of the shader this descriptor will be use
         * @return Corresponding descriptor set layout binding
         */
        vk::DescriptorSetLayoutBinding create_descriptor_image_sampler(int binding, vk::ShaderStageFlags const &shader);
        /**
         * Create a descriptor set layout from descriptor set layout binding pass as parameters
         * @param context: Vulkan context
         * @param set_layout_bindings: vector of descriptor set layout binding
         * @return Corresponding descriptor set layout
         */
        vk::DescriptorSetLayout create_descriptorset_layout(Context const &context,
                                                            std::vector<vk::DescriptorSetLayoutBinding> &&set_layout_bindings);
    }
#endif //MOUNTAIN_API_DESCRIPTORSET_LAYOUT_H
