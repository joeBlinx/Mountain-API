//
// Created by stiven_perso on 2/28/21.
//

#ifndef MOUNTAIN_API_PIPELINE_BUILDER_H
#define MOUNTAIN_API_PIPELINE_BUILDER_H
#include <vulkan/vulkan.hpp>
#include "mountain/graphics_pipeline.h"
#include <vector>
#include "subpass.h"
#include <span>
#include "mountain/mountainapi_export.h"
namespace mountain{

    struct PipelineBuilder{
    private:
        struct Subpass {
            template<class ...PushConstantType>
            PipelineBuilder &
            create_pipeline_layout(std::span<vk::DescriptorSetLayout const> const descriptor_layout,
                                   PushConstant<PushConstantType> const &...push_constant);
            Subpass(PipelineBuilder& builder):_builder(builder){}
        private:
            PipelineBuilder &_builder;
        };

        struct MultiSampling {
            MOUNTAINAPI_EXPORT Subpass define_subpass(SubPass const &subpass);
            MultiSampling(PipelineBuilder& builder):_builder(builder){}
        private:
            PipelineBuilder &_builder;
        };

        struct Vertex {
            MOUNTAINAPI_EXPORT MultiSampling create_mutlisampling();
            Vertex(PipelineBuilder& builder):_builder(builder){}
        private:
            PipelineBuilder &_builder;
        };

        struct Shaders {
            MOUNTAINAPI_EXPORT Vertex create_vertex_info(const buffer::vertex &vertex_buffer);
            Shaders(PipelineBuilder& builder):_builder(builder){}
        private:
            PipelineBuilder &_builder;
        };

        struct ColorBlendState {
            MOUNTAINAPI_EXPORT Shaders create_shaders_info(std::span<const shader> const shaders);
            ColorBlendState(PipelineBuilder& builder):_builder(builder){}
        private:
            PipelineBuilder &_builder;
        };

        struct DepthStencil {
            MOUNTAINAPI_EXPORT ColorBlendState create_color_blend_state();
            DepthStencil(PipelineBuilder& builder):_builder(builder){}
        private:
            PipelineBuilder &_builder;
        };

        struct Viewport {
            MOUNTAINAPI_EXPORT DepthStencil
            create_depth_stencil_state(vk::PipelineDepthStencilStateCreateInfo const &depth_stencil);
            Viewport(PipelineBuilder& builder):_builder(builder){}
        private:
            PipelineBuilder &_builder;
        };

        struct Rasterizer {
            MOUNTAINAPI_EXPORT Viewport create_viewport_info(vk::Extent2D const &extent);
            Rasterizer(PipelineBuilder& builder):_builder(builder){}
        private:
            PipelineBuilder &_builder;
        };

        struct Assembly {
            MOUNTAINAPI_EXPORT Rasterizer create_rasterizer(vk::PolygonMode const polygon_mode);
            Assembly(PipelineBuilder& builder):_builder(builder){}
      private:
            PipelineBuilder &_builder;
        };

        PipelineBuilder& create_viewport_info(vk::Extent2D const& extent);
        PipelineBuilder& create_depth_stencil_state(vk::PipelineDepthStencilStateCreateInfo const& depth_stencil);
        PipelineBuilder& create_color_blend_state();
        PipelineBuilder& create_shaders_info(std::span<const shader> const shaders);
        PipelineBuilder& create_vertex_info(const buffer::vertex &vertex_buffer);
        PipelineBuilder& create_rasterizer(vk::PolygonMode const polygon_mode);
        PipelineBuilder& create_mutlisampling();
        PipelineBuilder& define_subpass(SubPass const& subpass);

        template<class ...PushConstantType>
        PipelineBuilder& create_pipeline_layout(std::span<vk::DescriptorSetLayout const> const descriptor_layout,
                                                PushConstant<PushConstantType> const& ...push_constant);
    public:
        MOUNTAINAPI_EXPORT explicit PipelineBuilder(Context const& context);
        MOUNTAINAPI_EXPORT Assembly create_assembly(vk::PrimitiveTopology const  topology);
        MOUNTAINAPI_EXPORT GraphicsPipeline build();

    private:
        vk::UniqueShaderModule create_shader_module(std::vector<char> const &code);

        vk::PipelineInputAssemblyStateCreateInfo _assembly{};
        vk::Viewport _viewport;
        vk::Rect2D _scissor;
        vk::PipelineViewportStateCreateInfo _viewport_info{};
        vk::PipelineDepthStencilStateCreateInfo _depth_stencil{};
        vk::PipelineColorBlendAttachmentState _color_blend_attachment{};
        vk::PipelineColorBlendStateCreateInfo _color_blend_sate{};
        std::vector<vk::PipelineShaderStageCreateInfo> _shaders{};
        std::vector<vk::UniqueShaderModule> _shaders_module{};
        std::vector<vk::VertexInputAttributeDescription> _attribute_descriptions;
        std::vector<vk::VertexInputBindingDescription> _bindings_descriptions;
        vk::PipelineVertexInputStateCreateInfo _vertex_info{};
        vk::PipelineRasterizationStateCreateInfo _rasterizer{};
        vk::PipelineMultisampleStateCreateInfo _multisampling{};
        vk::PipelineLayoutCreateInfo _pipeline_layout_info{};
        SubPass _subpass{};
        Context const& _context;

        GraphicsPipeline _pipeline{};

    };

    template<class... PushConstantType>
    PipelineBuilder &
    PipelineBuilder::Subpass::create_pipeline_layout(const std::span<const vk::DescriptorSetLayout> descriptor_layout,
                                                     const PushConstant<PushConstantType> &... push_constant) {
        _builder.create_pipeline_layout(descriptor_layout, push_constant...);
        return _builder;
    }


    template<class... PushConstantType>
    PipelineBuilder &
    PipelineBuilder::create_pipeline_layout(const std::span<vk::DescriptorSetLayout const> descriptor_layout,
                                            const PushConstant <PushConstantType> &... push_constant) {
        uint32_t offset = 0;
        auto create_push_constant_ranges = [&offset]<class T>(PushConstant<T> const &push_constant) mutable {
            vk::PushConstantRange range(push_constant.shader_stage, offset, static_cast<uint32_t>(sizeof(T)));
            offset += sizeof(T);
            return range;
        };
        if constexpr (sizeof...(push_constant) > 0) {
            _pipeline._push_constant_ranges = std::vector{create_push_constant_ranges(push_constant)...};
        }
        _pipeline_layout_info.setLayoutCount = static_cast<uint32_t>(descriptor_layout.size());
        _pipeline_layout_info.pSetLayouts = descriptor_layout.data();
        _pipeline_layout_info.pushConstantRangeCount = static_cast<uint32_t>(_pipeline._push_constant_ranges.size());
        _pipeline_layout_info.pPushConstantRanges = _pipeline._push_constant_ranges.data();

        _pipeline._pipeline_layout = _context->createPipelineLayoutUnique(_pipeline_layout_info);

        return *this;
    }

}
#endif //MOUNTAIN_API_PIPELINE_BUILDER_H
