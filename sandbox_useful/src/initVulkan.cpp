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
#include <sandbox_useful/buffer/vertex.hpp>

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

    _device.free(_commandPool, _commandBuffers);

	for (auto &framebuffer : _swapchainFrameBuffer) {
		_device.destroy(framebuffer);
	}

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
//unique by software
void InitVulkan::createCommandBuffers(const std::vector<buffer::vertex> &buffers)
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

		for(auto const& vertex_buffer : buffers){
            _commandBuffers[i].bindVertexBuffers(0, 1, &vertex_buffer.get_buffer(), std::vector<vk::DeviceSize>{0}.data());
            _commandBuffers[i].bindIndexBuffer(vertex_buffer.get_buffer(), vertex_buffer.get_indices_offset(), vk::IndexType::eUint16);
            vkCmdDrawIndexed(_commandBuffers[i], vertex_buffer.get_indices_count(), 1, 0, 0, 0); // draw buffer
        }

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

InitVulkan::InitVulkan(const BasicInit &context, const Device &device, const SwapChain &swap_chain,
                       RenderPass const &renderpass, GraphicsPipeline const &graphics_pipeline,
                       const std::vector<buffer::vertex> &buffers)
		: _instance( context.get_vk_instance()), _surface(context.get_vk_surface()),
		  _swapchain( swap_chain.get_swap_chain()),
		  _swapChainImageViews(swap_chain.get_swap_chain_image_views()),
		  _swapChainImageFormat(swap_chain.get_swap_chain_image_format()),
		  _swapChainExtent(swap_chain.get_swap_chain_extent()),
		  _physicalDevice( device.get_physical_device()),
		  _device(device.get_device()),
		  _indices(device.get_queue_family_indice()),
		  _graphicsPipeline(graphics_pipeline.get_pipeline()),
		  _commandPool(device.get_command_pool()),
		  _graphicsQueue(device.get_graphics_queue()),
		  _presentQueue(device.get_present_queue()),
		  _renderpass(renderpass.get_renderpass()){
	_width = 1366;
	_height = 768;
    createFrameBuffers();
    createCommandBuffers(buffers);
    createSemaphores();

}
