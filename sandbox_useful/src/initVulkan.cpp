//
// Created by joe on 05/08/18.
//

#include "initVulkan.hpp"
#include "utils/log.hpp"
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cstring>
#include <set>
#include <algorithm>
#include "utils/utils.hpp"
#include <array>
#include <sandbox_useful/swapChain.hpp>
#include <sandbox_useful/context.hpp>
#include <sandbox_useful/buffer/vertex.hpp>


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

void InitVulkan::createSemaphores()
{
	_imageAvailableSemaphore = _device.createSemaphore({});
	_renderFinishedSemaphore = _device.createSemaphore({});
	
}

InitVulkan::InitVulkan(const Context &context, const SwapChain &swap_chain, RenderPass const &renderpass)
		:
		  _swapchain( swap_chain.get_swap_chain()),
		  _swapChainImageViews(swap_chain.get_swap_chain_image_views()),
		  _swapChainExtent(swap_chain.get_swap_chain_extent()),
		  _device(context.get_device()),
		  _commandPool(context.get_command_pool()),
		  _graphicsQueue(context.get_graphics_queue()),
		  _presentQueue(context.get_present_queue()),
		  _renderpass(renderpass.get_renderpass()){
    createFrameBuffers();

    allocate_command_buffer();

    createSemaphores();

}

void InitVulkan::allocate_command_buffer() {
    _commandBuffers.resize(_swapchainFrameBuffer.size());
    vk::CommandBufferAllocateInfo allocInfo = {};
    allocInfo.commandPool = _commandPool;
    allocInfo.level = vk::CommandBufferLevel::ePrimary;
    allocInfo.commandBufferCount = (uint32_t) _commandBuffers.size();
    _commandBuffers = _device.allocateCommandBuffers(allocInfo);
}
