//
// Created by joe on 05/08/18.
//

#include "initVulkan.hpp"
#include "utils/log.hpp"
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cstring>
#include <set>
#include <algorithm>
#include "utils/utils.hpp"
#include <array>
#include <sandbox_useful/swapChain.hpp>
#include <sandbox_useful/basicInit.hpp>
#include <sandbox_useful/buffer/array_buffer.hpp>



void InitVulkan::loop(GLFWwindow *window) {

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		drawFrame();
	}
	vkDeviceWaitIdle(_device);
}
void InitVulkan::drawFrame()
{
	uint32_t imageIndex;
	vkAcquireNextImageKHR(_device, _swapchain, std::numeric_limits<uint64_t>::max(), _imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

	vk::SubmitInfo submitInfo;
	vk::Semaphore waitSemaphores[] = { _imageAvailableSemaphore };

	vk::PipelineStageFlags waitStages[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &_commandBuffers[imageIndex];

	vk::Semaphore signalSemaphores[] = { _renderFinishedSemaphore };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;
	checkError(vkQueueSubmit(_graphicsQueue, 1, (VkSubmitInfo*)&submitInfo, VK_NULL_HANDLE),
		"failed to submit draw command buffer!");

	vk::PresentInfoKHR presentInfo = {};

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	vk::SwapchainKHR swapChains[] = { _swapchain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr; // Optional
	_presentQueue.presentKHR(presentInfo);
	_presentQueue.waitIdle();

}

InitVulkan::~InitVulkan() {
    _device.destroy(_renderFinishedSemaphore);
    _device.destroy(_imageAvailableSemaphore);
	_device.destroy(_commandPool);
	for (auto &framebuffer : _swapchainFrameBuffer) {
		_device.destroy(framebuffer);
	}
	_device.destroy(_graphicsPipeline);
	_device.destroy(_pipelineLayout);
}



vk::ShaderModule InitVulkan::createShaderModule(std::vector<char> const & code)
{ // RAII possible
	vk::ShaderModuleCreateInfo createInfo{};
	createInfo.codeSize = code.size();
	createInfo.pCode = (uint32_t*)code.data();
	vk::ShaderModule module = _device.createShaderModule(createInfo);
	
	return module;

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
vk::PipelineViewportStateCreateInfo createViewportPipeline(vk::Extent2D const & swapchainExtent)
{

	//*********VIEW PORT*************
	static vk::Viewport viewport ; // TODO: static ?? caca /20 ?
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float)swapchainExtent.width;
	viewport.height = (float)swapchainExtent.height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	static vk::Rect2D scissor = {};// TODO: static ?? caca /20 ?
	scissor.offset = vk::Offset2D{ 0, 0 };
	scissor.extent = swapchainExtent;

	vk::PipelineViewportStateCreateInfo viewportState = {};
	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;

	return viewportState;
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
void InitVulkan::createPipelineLayout() // lot of parameter
{
	vk::PipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.setLayoutCount = 0; // Optional
	pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
	pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
	pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional
	_pipelineLayout = _device.createPipelineLayout(pipelineLayoutInfo);
	
}

// some parameter
void InitVulkan::createRenderPass()
{
	vk::AttachmentDescription colorAttachment;
	colorAttachment.format = _swapChainImageFormat;
	colorAttachment.samples = vk::SampleCountFlagBits::e1;
	colorAttachment.loadOp = vk::AttachmentLoadOp::eClear;
	colorAttachment.storeOp = vk::AttachmentStoreOp::eStore;
	colorAttachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
	colorAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
	colorAttachment.initialLayout = vk::ImageLayout::eUndefined;
	colorAttachment.finalLayout = vk::ImageLayout::ePresentSrcKHR;

	vk::AttachmentReference colorAttachmentRef = {};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = vk::ImageLayout::eColorAttachmentOptimal;

	vk::SubpassDescription subpass = {};
	subpass.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;

	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	vk::SubpassDependency dependency = {};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
	dependency.srcAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;
	dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
	dependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentRead| vk::AccessFlagBits::eColorAttachmentWrite;

	vk::RenderPassCreateInfo renderPassInfo;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	renderPassInfo.dependencyCount = 1;
	renderPassInfo.pDependencies = &dependency;

	_renderpass = _device.createRenderPass(renderPassInfo);
	// checkError(vkCreateRenderPass(_device, &renderPassInfo, nullptr, &_renderpass), 
	// 	"failed to create render pass!");
	
}

//need parameter
void InitVulkan::createFrameBuffers()
{
	_swapchainFrameBuffer.resize(_swapChainImageViews.size());
	for (size_t i = 0; i < _swapChainImageViews.size(); i++)
	{
		vk::ImageView attachments[] = {
			_swapChainImageViews[i]
		};

		vk::FramebufferCreateInfo framebufferInfo;
		framebufferInfo.renderPass = _renderpass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = _swapChainExtent.width;
		framebufferInfo.height = _swapChainExtent.height;
		framebufferInfo.layers = 1;
		_swapchainFrameBuffer[i] = _device.createFramebuffer(framebufferInfo);
		
	
	}

}
void InitVulkan::createCommandPool()
{
	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = _indices.graphics_family;
	poolInfo.flags = 0; // Optional need parameter
	_commandPool = _device.createCommandPool(poolInfo);
	
	
}
//unique by software
void InitVulkan::createCommandBuffers()
{
	_commandBuffers.resize(_swapchainFrameBuffer.size());
	vk::CommandBufferAllocateInfo allocInfo = {};
	allocInfo.commandPool = _commandPool;
	allocInfo.level = vk::CommandBufferLevel::ePrimary;
	allocInfo.commandBufferCount = (uint32_t)_commandBuffers.size();
	_commandBuffers = _device.allocateCommandBuffers(allocInfo);
	

	for (size_t i = 0; i < _commandBuffers.size(); i++) {
		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		beginInfo.pInheritanceInfo = nullptr; // Optional

		checkError(vkBeginCommandBuffer(_commandBuffers[i], &beginInfo),
			"failed to begin recording command buffer!");
		/* may be can be put into a function */
		VkRenderPassBeginInfo renderPassInfo {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = _renderpass;
		renderPassInfo.framebuffer = _swapchainFrameBuffer[i];
		
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = _swapChainExtent;

		VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		vkCmdBindPipeline(_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, _graphicsPipeline); // bind the pipeline
		vkCmdDraw(_commandBuffers[i], 3, 1, 0, 0); // draw buffer

		vkCmdEndRenderPass(_commandBuffers[i]);
		checkError(vkEndCommandBuffer(_commandBuffers[i]),
			"failed to record command buffer!");
		
	}

}
void InitVulkan::createSemaphores()
{
	_imageAvailableSemaphore = _device.createSemaphore({});
	_renderFinishedSemaphore = _device.createSemaphore({});
	
}

InitVulkan::InitVulkan(const BasicInit &context, const Device &device, const SwapChain &swap_chain, RenderPass const& renderpass)
		: _instance( context.get_vk_instance()), _surface(context.get_vk_surface()),
		  _swapchain( swap_chain.get_swap_chain()),
		  _swapChainImageViews(swap_chain.get_swap_chain_image_views()),
		  _swapChainImageFormat(swap_chain.get_swap_chain_image_format()),
		  _swapChainExtent(swap_chain.get_swap_chain_extent()),
		  _physicalDevice( device.get_physical_device()),
		  _device(device.get_device()),
		  _indices(device.get_queue_family_indice()),
		  _graphicsQueue(device.get_graphics_queue()),
		  _presentQueue(device.get_present_queue()),
		  _renderpass(renderpass.get_renderpass()){
	_width = 1366;
	_height = 768;

}
