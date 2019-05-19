//
// Created by joe on 05/08/18.
//

#include "../include/initVulkan.hpp"
#include "../include/log.hpp"
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cstring>
#include <set>
#include <algorithm>
#include "../include/utils.hpp"
#include <array>


InitVulkan::InitVulkan(int width, int height) : _width(width),
												_height(height) {


	createRenderPass();
	createPipelineLayout();
	createGraphicsPipeline();
	createFrameBuffers();
	createCommandPool();
	createCommandBuffers();
	createSemaphores();
}

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

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { _imageAvailableSemaphore };

	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &_commandBuffers[imageIndex];

	VkSemaphore signalSemaphores[] = { _renderFinishedSemaphore };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	checkError(vkQueueSubmit(_graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE),
		"failed to submit draw command buffer!");

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = { _swapchain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr; // Optional
	vkQueuePresentKHR(_presentQueue, &presentInfo);

	vkQueueWaitIdle(_presentQueue);

}

InitVulkan::~InitVulkan() {

	vkDestroySemaphore(_device, _renderFinishedSemaphore, nullptr);
	vkDestroySemaphore(_device, _imageAvailableSemaphore, nullptr);
	vkDestroyCommandPool(_device, _commandPool, nullptr);
	for (auto &framebuffer : _swapchainFrameBuffer) {
		vkDestroyFramebuffer(_device, framebuffer, nullptr);
	}
	vkDestroyPipeline(_device, _graphicsPipeline, nullptr);
	vkDestroyPipelineLayout(_device, _pipelineLayout, nullptr);
//	vkDestroyRenderPass(_device, _renderpass, nullptr);

}



VkShaderModule InitVulkan::createShaderModule(std::vector<char> const & code)
{ // RAII possible
	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = (uint32_t*)code.data();
	VkShaderModule module;
	checkError(vkCreateShaderModule(_device, &createInfo, nullptr, &module),
		"failed to create Shader");

	return module;

}
VkPipelineShaderStageCreateInfo createShaderInfo(VkShaderModule & module, VkShaderStageFlagBits type)
{
	VkPipelineShaderStageCreateInfo info{};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	info.stage = type;
	info.module = module;
	info.pName = "main";
	return info;
}
VkPipelineInputAssemblyStateCreateInfo createAssembly(VkPrimitiveTopology topology)
{	//function needed
	VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = topology; // 3 vertices, one triangle
	inputAssembly.primitiveRestartEnable = VK_FALSE;
	return inputAssembly;

}
VkPipelineViewportStateCreateInfo createViewportPipeline(VkExtent2D const & swapchainExtent)
{

	//*********VIEW PORT*************
	static VkViewport viewport = {};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float)swapchainExtent.width;
	viewport.height = (float)swapchainExtent.height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	static VkRect2D scissor = {};
	scissor.offset = { 0, 0 };
	scissor.extent = swapchainExtent;

	VkPipelineViewportStateCreateInfo viewportState = {};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;

	return viewportState;
}
//need parameter in further modification
VkPipelineRasterizationStateCreateInfo createRasterizer()
{
	VkPipelineRasterizationStateCreateInfo rasterizer  {};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;
	rasterizer.depthBiasConstantFactor = 0.0f; // Optional
	rasterizer.depthBiasClamp = 0.0f; // Optional
	rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

	return rasterizer;
}
//need parameter in further modification
VkPipelineMultisampleStateCreateInfo createMultisampling()
{
	VkPipelineMultisampleStateCreateInfo multisampling {};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	multisampling.minSampleShading = 1.0f; // Optional
	multisampling.pSampleMask = nullptr; // Optional
	multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
	multisampling.alphaToOneEnable = VK_FALSE; // Optional

	return multisampling;
}
VkPipelineColorBlendAttachmentState createColorBlendAttachement()
{
	VkPipelineColorBlendAttachmentState colorBlendAttachment{};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;
	colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
	colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
	colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
	colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
	colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
	colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional
	return colorBlendAttachment;
}
VkPipelineColorBlendStateCreateInfo createColorBlendState(VkPipelineColorBlendAttachmentState & colorBlend)
{
	VkPipelineColorBlendStateCreateInfo colorBlending = {};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
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
	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 0; // Optional
	pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
	pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
	pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

	checkError (vkCreatePipelineLayout(_device, &pipelineLayoutInfo, nullptr, &_pipelineLayout)
		,"failed to create pipeline layout!");
	
}
void InitVulkan::createGraphicsPipeline()
{
	std::vector<char> vertex = utils::readFile("trianglevert.spv");
	std::vector<char> fragment = utils::readFile("trianglefrag.spv");

	VkShaderModule vertexModule = createShaderModule(vertex);
	VkShaderModule fragmentModule = createShaderModule(fragment);

	VkPipelineShaderStageCreateInfo pipelineVertex = createShaderInfo(vertexModule,
		VK_SHADER_STAGE_VERTEX_BIT);
	VkPipelineShaderStageCreateInfo pipelineFrag = createShaderInfo(fragmentModule,
		VK_SHADER_STAGE_FRAGMENT_BIT);

	std::vector<VkPipelineShaderStageCreateInfo> shaderStage{ pipelineVertex,pipelineFrag };

	// vertex Input defintion -> in function ?
	VkPipelineVertexInputStateCreateInfo vertexInput{};
	vertexInput.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInput.vertexBindingDescriptionCount = 0; // no vertex buffer
	vertexInput.pVertexBindingDescriptions = nullptr; // Optional
	vertexInput.vertexAttributeDescriptionCount = 0; // no attribute
	vertexInput.pVertexAttributeDescriptions = nullptr; // Optional


	// define the topology the vertices  and what kind of geometry
	
	VkPipelineInputAssemblyStateCreateInfo inputAssembly = createAssembly(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);

	VkPipelineViewportStateCreateInfo viewportState = createViewportPipeline(_swapChainExtent);

	VkPipelineRasterizationStateCreateInfo rasterizer = createRasterizer();
	VkPipelineMultisampleStateCreateInfo multisampling = createMultisampling();

	// DEPTH AND STENCIL

	// COLOR_RENDERING
	VkPipelineColorBlendAttachmentState colorBlendAttachement = createColorBlendAttachement();
	VkPipelineColorBlendStateCreateInfo colorBlending = createColorBlendState(colorBlendAttachement);

	std::array shaderStages{ pipelineVertex, pipelineFrag };

	/**can be factorised in function
	*/
	VkGraphicsPipelineCreateInfo pipelineInfo  {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = shaderStages.size();
	pipelineInfo.pStages = shaderStages.data();

	pipelineInfo.pVertexInputState = &vertexInput;
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
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
	pipelineInfo.basePipelineIndex = -1; // Optional
	checkError(vkCreateGraphicsPipelines(_device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &_graphicsPipeline)
		, "failed to create graphics pipeline!"
	);

	vkDestroyShaderModule(_device, fragmentModule, nullptr);
	vkDestroyShaderModule(_device, vertexModule, nullptr);

}
// some parameter
void InitVulkan::createRenderPass()
{
	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = _swapChainImageFormat;
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef = {};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	VkSubpassDependency dependency = {};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = 0;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	renderPassInfo.dependencyCount = 1;
	renderPassInfo.pDependencies = &dependency;


	checkError(vkCreateRenderPass(_device, &renderPassInfo, nullptr, &_renderpass), 
		"failed to create render pass!");
	
}

//need parameter
void InitVulkan::createFrameBuffers()
{
	_swapchainFrameBuffer.resize(_swapChainImageViews.size());
	for (size_t i = 0; i < _swapChainImageViews.size(); i++)
	{
		VkImageView attachments[] = {
			_swapChainImageViews[i]
		};

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = _renderpass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = _swapChainExtent.width;
		framebufferInfo.height = _swapChainExtent.height;
		framebufferInfo.layers = 1;

		checkError (vkCreateFramebuffer(_device, &framebufferInfo, nullptr, &_swapchainFrameBuffer[i]),
			"failed to create framebuffer!");
		
	}

}
void InitVulkan::createCommandPool()
{
	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = _indices.graphics_family;
	poolInfo.flags = 0; // Optional need parameter

	checkError (vkCreateCommandPool(_device, &poolInfo, nullptr, &_commandPool),
		"failed to create command pool!");
	
}
//unique by software
void InitVulkan::createCommandBuffers()
{
	_commandBuffers.resize(_swapchainFrameBuffer.size());
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = _commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)_commandBuffers.size();

	checkError (vkAllocateCommandBuffers(_device, &allocInfo, _commandBuffers.data()),
		"failed to allocate command buffers!");

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
	VkSemaphoreCreateInfo semaphoreInfo {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	checkError(vkCreateSemaphore(_device, &semaphoreInfo, nullptr, &_imageAvailableSemaphore),
			"failed to create semaphores!");

	checkError(vkCreateSemaphore(_device, &semaphoreInfo, nullptr, &_renderFinishedSemaphore),
		"failed to create semaphores!");


}

InitVulkan::InitVulkan(VkInstance instance, VkSurfaceKHR surface, VkDevice device, VkQueue graphics,
					   VkQueue present, VkPhysicalDevice physics, VkSwapchainKHR swap_chain,
					   std::vector<VkImageView> const &image_views, VkExtent2D extent, VkFormat format,
					   Device::QueueFamilyIndices const &indices, VkRenderPass renderpass)
		: _instance(instance), _surface(surface),
		  _swapchain(swap_chain),
		  _swapChainImageViews(image_views),
		  _swapChainImageFormat(format),
		  _swapChainExtent(extent),
		  _physicalDevice(physics),
		  _device(device),
		  _indices(indices),
		  _graphicsQueue(graphics),
		  _presentQueue(present),
		  _renderpass(renderpass){
	_width = 1366;
	_height = 768;


//	createRenderPass();
	createPipelineLayout();
	createGraphicsPipeline();
	createFrameBuffers();
	createCommandPool();
	createCommandBuffers();
	createSemaphores();
}
