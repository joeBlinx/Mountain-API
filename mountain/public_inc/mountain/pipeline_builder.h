//
// Created by stiven_perso on 2/28/21.
//

#ifndef MOUNTAIN_API_PIPELINE_BUILDER_H
#define MOUNTAIN_API_PIPELINE_BUILDER_H
#include <vulkan/vulkan.hpp>
#include "mountain/graphics_pipeline.h"
#include <vector>
#include "subpass.h"

namespace mountain{
    struct PipelineBuilder{
        PipelineBuilder& create_assembly(vk::PrimitiveTopology const topology);
        PipelineBuilder& create_viewport_info(vk::Extent2D const& extent);
        PipelineBuilder& create_depth_stencil_state(vk::PipelineDepthStencilStateCreateInfo const& depth_stencil);
        PipelineBuilder& create_color_blend_state();
        template<size_t n>
        PipelineBuilder& create_shaders_info(std::array<shader, n> const& shaders);
        PipelineBuilder& create_vertex_info();
        PipelineBuilder& create_rasterizer();
        PipelineBuilder& create_mutlisampling();
        PipelineBuilder& define_subpass(SubPass const& subpass);


        template<class ...PushConstantType, std::size_t n>
        PipelineBuilder& create_pipeline_layout(std::array<vk::DescriptorSetLayout, n> const& descriptor_layout,
                                                PushConstant<PushConstantType> const& ...push_constant);

    private:
        vk::PipelineInputAssemblyStateCreateInfo _assembly{};
        vk::Viewport _viewport;
        vk::Rect2D _scissor;
        vk::PipelineViewportStateCreateInfo _viewport_info{};
        vk::PipelineDepthStencilStateCreateInfo _depth_stencil{};
    vk::PipelineColorBlendAttachmentState _color_blend_attachment{};
        vk::PipelineColorBlendStateCreateInfo _color_blend_sate{};
        std::vector<vk::PipelineShaderStageCreateInfo> _shaders{};
        vk::UniquePipelineLayout _pipeline_layout{};
        vk::PipelineVertexInputStateCreateInfo _vertex_info{};
        vk::PipelineRasterizationStateCreateInfo _rasterizer{};
        vk::PipelineMultisampleStateCreateInfo _multisampling{};
        SubPass _subpass{};

    };



    template<size_t n>
    PipelineBuilder &PipelineBuilder::create_shaders_info(const std::array<shader, n> &shaders) {
        return <#initializer#>;
    }

    template<class... PushConstantType, std::size_t n>
    PipelineBuilder &
    PipelineBuilder::create_pipeline_layout(const std::array<vk::DescriptorSetLayout, n> &descriptor_layout,
                                            const PushConstant <PushConstantType> &... push_constant) {
        return <#initializer#>;
    }
}
#endif //MOUNTAIN_API_PIPELINE_BUILDER_H
