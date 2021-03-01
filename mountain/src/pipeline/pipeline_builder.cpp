//
// Created by stiven_perso on 2/28/21.
//
#include "mountain/pipeline_builder.h"
namespace mountain{
    PipelineBuilder &PipelineBuilder::create_assembly(const vk::PrimitiveTopology topology) {
        _assembly.topology = topology; // 3 vertices, one triangle
        _assembly.primitiveRestartEnable = VK_FALSE;
        return *this;
    }

    PipelineBuilder &PipelineBuilder::create_viewport_info(const vk::Extent2D &extent) {
        _viewport.x = 0.0f;
        _viewport.y = 0.0f;
        _viewport.width = (float) extent.width;
        _viewport.height = (float) extent.height;
        _viewport.minDepth = 0.0f;
        _viewport.maxDepth = 1.0f;
        _scissor.offset = vk::Offset2D{0, 0};
        _scissor.extent = extent;

        _viewport_info.viewportCount = 1;
        _viewport_info.pViewports = &_viewport;
        _viewport_info.scissorCount = 1;
        _viewport_info.pScissors = &_scissor;
        return *this;
    }

    PipelineBuilder &
    PipelineBuilder::create_depth_stencil_state(const vk::PipelineDepthStencilStateCreateInfo &depth_stencil) {
        _depth_stencil = depth_stencil;
        return *this;
    }

    PipelineBuilder &PipelineBuilder::create_color_blend_state() {
        _color_blend_attachment.colorWriteMask =
                vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB |
                vk::ColorComponentFlagBits::eA;
        _color_blend_attachment.blendEnable = VK_FALSE;
        _color_blend_sate.logicOpEnable = VK_FALSE;
        _color_blend_sate.attachmentCount = 1;
        _color_blend_sate.pAttachments = &_color_blend_attachment;
        return *this;
    }

    PipelineBuilder &PipelineBuilder::create_vertex_info() {
        return *this;
    }

    PipelineBuilder &PipelineBuilder::create_rasterizer() {
        _rasterizer.depthClampEnable = VK_FALSE;
        _rasterizer.rasterizerDiscardEnable = VK_FALSE;
        _rasterizer.polygonMode = vk::PolygonMode::eFill;
        _rasterizer.lineWidth = 1.0f;
        _rasterizer.cullMode = vk::CullModeFlagBits::eNone;
        _rasterizer.frontFace = vk::FrontFace::eCounterClockwise;
        _rasterizer.depthBiasEnable = VK_FALSE;
        return *this;
    }

    PipelineBuilder &PipelineBuilder::create_mutlisampling() {
        return *this;
    }

    PipelineBuilder &PipelineBuilder::define_subpass(const SubPass &subpass) {
        return *this;
    }
}