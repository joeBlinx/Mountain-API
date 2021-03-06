//
// Created by stiven_perso on 2/28/21.
//
#include "mountain/pipeline_builder.h"
#include "mountain/render_pass.h"
namespace mountain{
    vk::PipelineShaderStageCreateInfo create_pipeline_shader(vk::ShaderModule const &module, vk::ShaderStageFlagBits type) {
        vk::PipelineShaderStageCreateInfo info;
        info.stage = type;
        info.module = module;
        info.pName = "main";
        return info;
    }
    vk::UniqueShaderModule PipelineBuilder::create_shader_module(std::vector<char> const &code) { // RAII possible
        vk::ShaderModuleCreateInfo createInfo{};
        createInfo.codeSize = code.size();
        createInfo.pCode = (uint32_t *) code.data();
        return _context->createShaderModuleUnique(createInfo);
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
    PipelineBuilder::PipelineBuilder(Context const& context):_context(context) {
        _pipeline_layout_info.setLayoutCount = 0;
        _pipeline_layout_info.pSetLayouts = nullptr;
        _pipeline_layout_info.pushConstantRangeCount = 0;
        _pipeline_layout_info.pPushConstantRanges = nullptr;
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


    PipelineBuilder &PipelineBuilder::create_rasterizer(vk::PolygonMode const polygon_mode) {
        _rasterizer.depthClampEnable = VK_FALSE;
        _rasterizer.rasterizerDiscardEnable = VK_FALSE;
        _rasterizer.polygonMode = polygon_mode;
        _rasterizer.lineWidth = 1.0f;
        _rasterizer.cullMode = vk::CullModeFlagBits::eNone;
        _rasterizer.frontFace = vk::FrontFace::eCounterClockwise;
        _rasterizer.depthBiasEnable = VK_FALSE;
        return *this;
    }

    PipelineBuilder &PipelineBuilder::create_mutlisampling() {
        _multisampling.sampleShadingEnable = VK_FALSE;
        _multisampling.rasterizationSamples = vk::SampleCountFlagBits::e1;
        _multisampling.minSampleShading = 1.0f; // Optional
        _multisampling.pSampleMask = nullptr; // Optional
        _multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
        _multisampling.alphaToOneEnable = VK_FALSE; // Optional
        return *this;
    }

    PipelineBuilder &PipelineBuilder::define_subpass(const SubPass &subpass) {
        _subpass = subpass;
        return *this;
    }

    GraphicsPipeline PipelineBuilder::build() {
        vk::GraphicsPipelineCreateInfo pipelineInfo{};
        pipelineInfo.stageCount = static_cast<uint32_t>(_shaders.size());
        pipelineInfo.pStages = _shaders.data();

        pipelineInfo.pVertexInputState = &_vertex_info;
        pipelineInfo.pInputAssemblyState = &_assembly;
        pipelineInfo.pViewportState = &_viewport_info;
        pipelineInfo.pRasterizationState = &_rasterizer;
        pipelineInfo.pMultisampleState = &_multisampling;
        auto const& render_pass = _subpass.renderpass;
        pipelineInfo.pDepthStencilState = render_pass->has_depth_or_stencil() ? &_depth_stencil : nullptr;
        pipelineInfo.pColorBlendState = &_color_blend_sate;

        pipelineInfo.layout = *_pipeline._pipeline_layout;
        pipelineInfo.renderPass = render_pass->get_renderpass();
        pipelineInfo.subpass = _subpass.index;

        _pipeline._pipeline = _context->createGraphicsPipelineUnique(nullptr, pipelineInfo).value;

        return std::move(_pipeline);
    }

    PipelineBuilder &PipelineBuilder::create_vertex_info(const buffer::vertex &vertex_buffer) {

        std::copy(begin(vertex_buffer.get_attributes()), end(vertex_buffer.get_attributes()),
                      std::back_inserter(_attribute_descriptions));

        _bindings_descriptions.emplace_back(vertex_buffer.get_bindings());

        _vertex_info.vertexBindingDescriptionCount = static_cast<uint32_t>(_bindings_descriptions.size());
        _vertex_info.pVertexBindingDescriptions = _bindings_descriptions.data();
        _vertex_info.vertexAttributeDescriptionCount = static_cast<uint32_t>(_attribute_descriptions.size());
        _vertex_info.pVertexAttributeDescriptions = _attribute_descriptions.data();
        return *this;
    }

    PipelineBuilder &PipelineBuilder::create_shaders_info(std::span<const shader> const shaders) {
        _shaders.reserve(size(shaders));
        _shaders_module.reserve(size(shaders));
        std::ranges::for_each(shaders, [this](auto const &shader)mutable {
            std::vector<char> shader_data = utils::readFile(shader.path.string());
            auto const& module = _shaders_module.emplace_back(create_shader_module(shader_data));
            _shaders.emplace_back(create_pipeline_shader(
                    *module,
                    shader.type
            ));
        });
        return *this;
    }

    PipelineBuilder::Assembly PipelineBuilder::create_assembly(const vk::PrimitiveTopology topology) {
        _assembly.topology = topology; // 3 vertices, one triangle
        _assembly.primitiveRestartEnable = VK_FALSE;
        return Assembly{*this};
    }

    PipelineBuilder::Rasterizer PipelineBuilder::Assembly::create_rasterizer(const vk::PolygonMode polygon_mode) {
        _builder.create_rasterizer(polygon_mode);
        return {_builder};
    }

    PipelineBuilder::Viewport PipelineBuilder::Rasterizer::create_viewport_info(const vk::Extent2D &extent) {
        _builder.create_viewport_info(extent);
        return {_builder};
    }

    PipelineBuilder::DepthStencil PipelineBuilder::Viewport::create_depth_stencil_state(
            const vk::PipelineDepthStencilStateCreateInfo &depth_stencil) {
        _builder.create_depth_stencil_state(depth_stencil);
        return {_builder};
    }

    PipelineBuilder::ColorBlendState PipelineBuilder::DepthStencil::create_color_blend_state() {
        _builder.create_color_blend_state();
        return {_builder};
    }

    PipelineBuilder::Shaders
    PipelineBuilder::ColorBlendState::create_shaders_info(const std::span<const shader> shaders) {
        _builder.create_shaders_info(shaders);
        return {_builder};
    }

    PipelineBuilder::Vertex PipelineBuilder::Shaders::create_vertex_info(const buffer::vertex &vertex_buffer) {
        _builder.create_vertex_info(vertex_buffer);
        return {_builder};
    }

    PipelineBuilder::MultiSampling PipelineBuilder::Vertex::create_mutlisampling() {
        _builder.create_mutlisampling();
        return {_builder};
    }

    PipelineBuilder::Subpass PipelineBuilder::MultiSampling::define_subpass(const SubPass &subpass) {
        _builder.define_subpass(subpass);
        return {_builder};
    }
}