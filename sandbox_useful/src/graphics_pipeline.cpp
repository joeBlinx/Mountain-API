//
// Created by stiven on 13/04/2020.
//

#include "graphics_pipeline.hpp"
#include "utils/utils.hpp"
#include "context.hpp"
#include "swapChain.hpp"
#include "renderPass.hpp"
vk::PipelineShaderStageCreateInfo createShaderInfo(vk::ShaderModule & module, vk::ShaderStageFlagBits type);
vk::PipelineInputAssemblyStateCreateInfo createAssembly(vk::PrimitiveTopology topology);
//need parameter in further modification
vk::PipelineRasterizationStateCreateInfo createRasterizer();
//need parameter in further modification
vk::PipelineMultisampleStateCreateInfo createMultisampling();
vk::PipelineColorBlendAttachmentState createColorBlendAttachement();
vk::PipelineColorBlendStateCreateInfo createColorBlendState(vk::PipelineColorBlendAttachmentState & colorBlend);

struct VertexInfo{
private:
    std::vector<vk::VertexInputAttributeDescription> attribute_descriptions;
    std::vector<vk::VertexInputBindingDescription> bindings_descriptions;
public:
    vk::PipelineVertexInputStateCreateInfo create_info;
    explicit VertexInfo(std::vector<buffer::vertex> const& buffers){
        std::for_each(begin(buffers), end(buffers), [this](buffer::vertex const& buffer){
            std::copy(begin(buffer.get_attributes()), end(buffer.get_attributes()), std::back_inserter(attribute_descriptions));
            bindings_descriptions.emplace_back(buffer.get_bindings());
        });


        create_info.vertexBindingDescriptionCount = bindings_descriptions.size();
        create_info.pVertexBindingDescriptions = bindings_descriptions.data();
        create_info.vertexAttributeDescriptionCount = attribute_descriptions.size();
        create_info.pVertexAttributeDescriptions = attribute_descriptions.data();
    }
};
struct pipelineViewPortInfo{
    vk::PipelineViewportStateCreateInfo viewport_info;
    pipelineViewPortInfo(vk::Extent2D const& swapchainExtent){

        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)swapchainExtent.width;
        viewport.height = (float)swapchainExtent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        scissor.offset = vk::Offset2D{ 0, 0 };
        scissor.extent = swapchainExtent;

        viewport_info.viewportCount = 1;
        viewport_info.pViewports = &viewport;
        viewport_info.scissorCount = 1;
        viewport_info.pScissors = &scissor;

    }

private:
    vk::Viewport viewport;
    vk::Rect2D scissor;
};


void GraphicsPipeline::init(const SwapChain &swap_chain, const RenderPass &render_pass,
                            const std::vector<buffer::vertex> &buffers) {
    std::vector<char> vertex = utils::readFile("trianglevert.spv");
    std::vector<char> fragment = utils::readFile("trianglefrag.spv");

    auto vertexModule = createShaderModule(vertex);
    auto fragmentModule = createShaderModule(fragment);

    auto pipelineVertex = createShaderInfo(vertexModule,
                                           vk::ShaderStageFlagBits::eVertex);
    auto pipelineFrag = createShaderInfo(fragmentModule,
                                         vk::ShaderStageFlagBits::eFragment);

    std::vector<vk::PipelineShaderStageCreateInfo> shaderStage{pipelineVertex, pipelineFrag};

    VertexInfo vertex_info(buffers);

    // define the topology the vertices  and what kind of geometry
    auto inputAssembly = createAssembly(vk::PrimitiveTopology::eTriangleList);

    pipelineViewPortInfo viewportState(swap_chain.get_swap_chain_extent());

    auto rasterizer = createRasterizer();
    auto multisampling = createMultisampling();

    // DEPTH AND STENCIL

    // COLOR_RENDERING
    auto colorBlendAttachement = createColorBlendAttachement();
    auto colorBlending = createColorBlendState(colorBlendAttachement);

    std::array shaderStages{ pipelineVertex, pipelineFrag };

    /**can be factorised in function
    */

    vk::GraphicsPipelineCreateInfo pipelineInfo  {};
    pipelineInfo.stageCount = shaderStages.size();
    pipelineInfo.pStages = shaderStages.data();

    pipelineInfo.pVertexInputState = &vertex_info.create_info;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState.viewport_info;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pDepthStencilState = nullptr; // Optional nostencil for now
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = nullptr; // Optional
    pipelineInfo.layout = *_pipeline_layout;
    pipelineInfo.renderPass = render_pass.get_renderpass();
    pipelineInfo.subpass = 0;
    // pipelineInfo.basePipelineHandle ; // Optional
    pipelineInfo.basePipelineIndex = -1; // Optional
    auto create_pipeline = [&]{ // create pipeline this way because for some reason I cannot use the c++ APi the same way on different computers
        VkPipeline temp_pipeline{};
        auto temp = (VkGraphicsPipelineCreateInfo)pipelineInfo;
        vkCreateGraphicsPipelines(_device.get_device(),nullptr, 1, &temp, nullptr, &temp_pipeline); // for some re
        return temp_pipeline;
    };
    _pipeline = create_pipeline();
    vkDestroyShaderModule(_device.get_device(), fragmentModule, nullptr);
    vkDestroyShaderModule(_device.get_device(), vertexModule, nullptr);
}


vk::ShaderModule GraphicsPipeline::createShaderModule(std::vector<char> const & code)
{ // RAII possible
    vk::ShaderModuleCreateInfo createInfo{};
    createInfo.codeSize = code.size();
    createInfo.pCode = (uint32_t*)code.data();
    vk::ShaderModule module = _device.get_device().createShaderModule(createInfo);

    return module;

}

GraphicsPipeline::~GraphicsPipeline() {
    _device.get_device().destroy(_pipeline);
}

vk::PipelineShaderStageCreateInfo createShaderInfo(vk::ShaderModule & module, vk::ShaderStageFlagBits type)
{
    vk::PipelineShaderStageCreateInfo info;
    info.stage = type;
    info.module = module;
    info.pName = "main";
    return info;
}
vk::PipelineInputAssemblyStateCreateInfo createAssembly(vk::PrimitiveTopology topology)
{	//function needed
    vk::PipelineInputAssemblyStateCreateInfo inputAssembly;
    inputAssembly.topology = topology; // 3 vertices, one triangle
    inputAssembly.primitiveRestartEnable = VK_FALSE;
    return inputAssembly;

}

//need parameter in further modification
vk::PipelineRasterizationStateCreateInfo createRasterizer()
{
    vk::PipelineRasterizationStateCreateInfo rasterizer  {};
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = vk::PolygonMode::eFill;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = vk::CullModeFlagBits::eBack;
    rasterizer.frontFace = vk::FrontFace::eClockwise;
    rasterizer.depthBiasEnable = VK_FALSE;
    rasterizer.depthBiasConstantFactor = 0.0f; // Optional
    rasterizer.depthBiasClamp = 0.0f; // Optional
    rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

    return rasterizer;
}
//need parameter in further modification
vk::PipelineMultisampleStateCreateInfo createMultisampling()
{
    vk::PipelineMultisampleStateCreateInfo multisampling {};
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = vk::SampleCountFlagBits::e1;
    multisampling.minSampleShading = 1.0f; // Optional
    multisampling.pSampleMask = nullptr; // Optional
    multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
    multisampling.alphaToOneEnable = VK_FALSE; // Optional

    return multisampling;
}
vk::PipelineColorBlendAttachmentState createColorBlendAttachement()
{
    vk::PipelineColorBlendAttachmentState colorBlendAttachment;
    colorBlendAttachment.colorWriteMask = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB |vk::ColorComponentFlagBits::eA;
    colorBlendAttachment.blendEnable = VK_FALSE;
    colorBlendAttachment.srcColorBlendFactor = vk::BlendFactor::eOne; // Optional
    colorBlendAttachment.dstColorBlendFactor = vk::BlendFactor::eZero; // Optional
    colorBlendAttachment.colorBlendOp = vk::BlendOp::eAdd; // Optional
    colorBlendAttachment.srcAlphaBlendFactor = vk::BlendFactor::eZero; // Optional
    colorBlendAttachment.dstAlphaBlendFactor = vk::BlendFactor::eZero; // Optional
    colorBlendAttachment.alphaBlendOp = vk::BlendOp::eAdd; // Optional
    return colorBlendAttachment;
}
vk::PipelineColorBlendStateCreateInfo createColorBlendState(vk::PipelineColorBlendAttachmentState & colorBlend)
{
    vk::PipelineColorBlendStateCreateInfo colorBlending = {};
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = vk::LogicOp::eCopy; // Optional
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlend;
    colorBlending.blendConstants[0] = 0.0f; // Optional
    colorBlending.blendConstants[1] = 0.0f; // Optional
    colorBlending.blendConstants[2] = 0.0f; // Optional
    colorBlending.blendConstants[3] = 0.0f; // Optional

    return colorBlending;
}