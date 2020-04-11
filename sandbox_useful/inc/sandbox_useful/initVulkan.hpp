//
// Created by joe on 05/08/18.
//

#ifndef SANDBOX_INITVULKAN_HPP
#define SANDBOX_INITVULKAN_HPP

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include "sandbox_useful/swapChain.hpp"
#include "sandbox_useful/basicInit.hpp"
#include "sandbox_useful/device.hpp"
#include "sandbox_useful/renderpass/renderPass.hpp"
#include "utils/utils.hpp"
#include "sandbox_useful/buffer/array_buffer.hpp"
#include <iostream>
struct InitVulkan {
private:
	InitVulkan(const BasicInit &context, const Device &device, const SwapChain &swap_chain, RenderPass const& renderpass);
public:
	void loop(GLFWwindow *window);
	~InitVulkan();
	template<class ...Ts>
	static InitVulkan create_vulkan(const BasicInit &context, const Device &device, const SwapChain &swap_chain, RenderPass const& renderpass, std::vector<vk::Buffer> const& buffers, Ts &&... vertex_description);

private:
	const std::vector<const char*> validationLayers {
			"VK_LAYER_LUNARG_standard_validation"
	};
	std::vector<const char*> const _devicesExtension{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
#ifdef NDEBUG
	static bool constexpr _enableValidationLayer = false;
#else
	static bool constexpr _enableValidationLayer = true;
#endif
	int _width, _height;
	vk::Instance _instance;
	vk::SurfaceKHR _surface;
	vk::SwapchainKHR _swapchain;

	std::vector<vk::ImageView> const& _swapChainImageViews;
	vk::Format _swapChainImageFormat;
	vk::Extent2D _swapChainExtent;
	vk::PhysicalDevice _physicalDevice;
	vk::Device _device;
	Device::QueueFamilyIndices _indices;
	vk::PipelineLayout _pipelineLayout;
	vk::Pipeline _graphicsPipeline;
	std::vector<vk::Framebuffer> _swapchainFrameBuffer;
	vk::CommandPool _commandPool;
	std::vector<vk::CommandBuffer> _commandBuffers;
	vk::Queue  _graphicsQueue;

	vk::Queue  _presentQueue;
	vk::RenderPass _renderpass;

	vk::Semaphore _imageAvailableSemaphore;
	vk::Semaphore _renderFinishedSemaphore;


	vk::ShaderModule createShaderModule(std::vector<char> const & code);
	template<class ...Ts>
	void createGraphicsPipeline(Ts &&... vertex_description); // multiple parameters but can surely be divide in some fucntions
	void createPipelineLayout(); // lot of parameter
	void createRenderPass();
	void createCommandPool();
	void createCommandBuffers(std::vector<vk::Buffer> const& buffers);
	void drawFrame();
	void createSemaphores();

	void createFrameBuffers();
};

template<class ...Ts>
InitVulkan InitVulkan::create_vulkan(const BasicInit &context, const Device &device, const SwapChain &swap_chain, RenderPass const& renderpass, std::vector<vk::Buffer> const& buffers, Ts &&... vertex_description){
	InitVulkan initvulkan(context, device, swap_chain, renderpass);
	initvulkan.createPipelineLayout();
	initvulkan.createGraphicsPipeline(std::forward<Ts>(vertex_description)...);
	initvulkan.createFrameBuffers();
	initvulkan.createCommandPool();
	initvulkan.createCommandBuffers(buffers);
	initvulkan.createSemaphores();
	return initvulkan;
}
template<class IT, class T, class ...Ts>
auto copy (IT it_begin, T& array){
				std::copy(std::begin(array), std::end(array), it_begin);
}
template<class IT, class T, class ...Ts>
void copy(IT it_begin, T& array, Ts&... arrays){
			copy(it_begin, array);
			std::advance(it_begin, array.size());
			copy(it_begin, arrays...);
}
template< class ...Ts>
struct VertexInfo{
private:
	std::array<vk::VertexInputAttributeDescription, (Ts::attributes_size+...)> attribute_descriptions;
	std::array<vk::VertexInputBindingDescription, sizeof...(Ts)> bindings_descriptions;
public:
	vk::PipelineVertexInputStateCreateInfo create_info;
	VertexInfo(Ts &... vertex_description){
		
		copy(std::begin(attribute_descriptions), vertex_description.attributes...);
		bindings_descriptions = std::array{vertex_description.bindings...};
		create_info.vertexBindingDescriptionCount = bindings_descriptions.size();
		create_info.pVertexBindingDescriptions = bindings_descriptions.data(); 
		create_info.vertexAttributeDescriptionCount = attribute_descriptions.size(); 
		create_info.pVertexAttributeDescriptions = attribute_descriptions.data();
	}
};


vk::PipelineShaderStageCreateInfo createShaderInfo(vk::ShaderModule & module, vk::ShaderStageFlagBits type);
vk::PipelineInputAssemblyStateCreateInfo createAssembly(vk::PrimitiveTopology topology);
vk::PipelineViewportStateCreateInfo createViewportPipeline(vk::Extent2D const & swapchainExtent);
//need parameter in further modification
vk::PipelineRasterizationStateCreateInfo createRasterizer();
//need parameter in further modification
vk::PipelineMultisampleStateCreateInfo createMultisampling();
vk::PipelineColorBlendAttachmentState createColorBlendAttachement();
vk::PipelineColorBlendStateCreateInfo createColorBlendState(vk::PipelineColorBlendAttachmentState & colorBlend);
template<class ...Ts>
void InitVulkan::createGraphicsPipeline(Ts &&... vertex_description)
{
	std::vector<char> vertex = utils::readFile("trianglevert.spv");
	std::vector<char> fragment = utils::readFile("trianglefrag.spv");

	auto vertexModule = createShaderModule(vertex);
	auto fragmentModule = createShaderModule(fragment);

	auto pipelineVertex = createShaderInfo(vertexModule,
		vk::ShaderStageFlagBits::eVertex);
	auto pipelineFrag = createShaderInfo(fragmentModule,
		vk::ShaderStageFlagBits::eFragment);

	std::vector<vk::PipelineShaderStageCreateInfo> shaderStage{ pipelineVertex,pipelineFrag };

	VertexInfo vertex_info(std::forward<Ts>(vertex_description)...);

	// define the topology the vertices  and what kind of geometry
	auto inputAssembly = createAssembly(vk::PrimitiveTopology::eTriangleList);

	auto viewportState = createViewportPipeline(_swapChainExtent);

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
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pDepthStencilState = nullptr; // Optional nostencil for now
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.pDynamicState = nullptr; // Optional
	pipelineInfo.layout = _pipelineLayout;
	pipelineInfo.renderPass = _renderpass;
	pipelineInfo.subpass = 0;
	// pipelineInfo.basePipelineHandle ; // Optional
	pipelineInfo.basePipelineIndex = -1; // Optional
	_graphicsPipeline = _device.createGraphicsPipeline({}, pipelineInfo).value;
	vkDestroyShaderModule(_device, fragmentModule, nullptr);
	vkDestroyShaderModule(_device, vertexModule, nullptr);

}
#endif //SANDBOX_INITVULKAN_HPP
