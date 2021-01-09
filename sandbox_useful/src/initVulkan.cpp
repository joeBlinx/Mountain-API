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
#include <uniform.h>

InitVulkan::InitVulkan(const Context &context, const SwapChain &swap_chain, RenderPass const &renderpass,
                       int nb_uniform)
        :
        _swapchain( swap_chain.get_swap_chain()),
        _swapChainImageViews(swap_chain.get_swap_chain_image_views()),
        _swapChainExtent(swap_chain.get_swap_chain_extent()),
        _context(context),
        _commandPool(context.get_command_pool()),
        _graphicsQueue(context.get_graphics_queue()),
        _presentQueue(context.get_present_queue()),
        _renderpass(renderpass.get_renderpass()){
    createFrameBuffers();

    allocate_command_buffer();
    create_descriptor_pool(nb_uniform);
    createSemaphores();

}
void InitVulkan::drawFrame(std::vector<buffer::uniform_updater> &&updaters)
{
	uint32_t imageIndex;
	vkAcquireNextImageKHR(_context.get_device(), _swapchain, std::numeric_limits<uint64_t>::max(), _imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

	for(auto& updater : updaters){
	    updater(_context, imageIndex);
	}
	
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
	checkError(_presentQueue.presentKHR(presentInfo),
            "unable to present frame buffer"
            );
	_presentQueue.waitIdle();

}

InitVulkan::~InitVulkan() {
    _context.get_device().destroy(_renderFinishedSemaphore);
    _context.get_device().destroy(_imageAvailableSemaphore);

    _context.get_device().free(_commandPool, _commandBuffers);

	for (auto &framebuffer : _swapchainFrameBuffer) {
		_context.get_device().destroy(framebuffer);
	}

	for(auto &descriptor_set_layout: _descriptor_set_layouts){
	    _context->destroy(descriptor_set_layout);
	}

}

//need parameter
void InitVulkan::createFrameBuffers()
{
	_swapchainFrameBuffer.resize(_swapChainImageViews.size());
	for (size_t i = 0; i < _swapChainImageViews.size(); i++)
	{
		vk::ImageView attachments[] = {
			*_swapChainImageViews[i]
		};

		vk::FramebufferCreateInfo framebufferInfo;
		framebufferInfo.renderPass = _renderpass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = _swapChainExtent.width;
		framebufferInfo.height = _swapChainExtent.height;
		framebufferInfo.layers = 1;
		_swapchainFrameBuffer[i] = _context.get_device().createFramebuffer(framebufferInfo);

	}

}
//unique by software

void InitVulkan::createSemaphores()
{
	_imageAvailableSemaphore = _context.get_device().createSemaphore({});
	_renderFinishedSemaphore = _context.get_device().createSemaphore({});
	
}

void InitVulkan::allocate_command_buffer() {
    _commandBuffers.resize(_swapchainFrameBuffer.size());
    vk::CommandBufferAllocateInfo allocInfo = {};
    allocInfo.commandPool = _commandPool;
    allocInfo.level = vk::CommandBufferLevel::ePrimary;
    allocInfo.commandBufferCount = (uint32_t) _commandBuffers.size();
    _commandBuffers = _context.get_device().allocateCommandBuffers(allocInfo);
}

void InitVulkan::create_descriptor_pool(int nb_uniform) {
    std::array<vk::DescriptorPoolSize,2> pool_size;
    pool_size[0].type = vk::DescriptorType::eUniformBuffer;
    pool_size[0].descriptorCount = _swapChainImageViews.size()*nb_uniform;

    pool_size[1].type = vk::DescriptorType::eCombinedImageSampler;
    pool_size[1].descriptorCount = _swapChainImageViews.size()*nb_uniform;

    vk::DescriptorPoolCreateInfo _pool_info;
    _pool_info.poolSizeCount = pool_size.size();
    _pool_info.pPoolSizes = pool_size.data();
    _pool_info.maxSets = _swapChainImageViews.size()*nb_uniform;


    _descriptor_pool = _context.get_device().createDescriptorPoolUnique(_pool_info);


}

void InitVulkan::allocate_descriptor_set(std::vector<vk::DescriptorSetLayout> &&descriptor_set_layouts) {
    /*
     * We use one descriptor set layout by image of the swap chain,
     * but for using multiple set layout, we store them as follow:
     * |A|B|A|B|A|B|
     * where A and B are different descriptor set layout
     * We order descriptor set this way to be able to use vkcmdBindDescriptorset with arrays
     */
    _descriptor_set_layouts = std::move(descriptor_set_layouts);
    size_t const nb_image_swap_chain = _swapChainImageViews.size();
    _nb_descriptor_set_by_image = _descriptor_set_layouts.size();
    std::vector<vk::DescriptorSetLayout> layouts;
    layouts.resize(nb_image_swap_chain * _nb_descriptor_set_by_image);

    for(auto it_set_layouts = begin(_descriptor_set_layouts); it_set_layouts != end(_descriptor_set_layouts); it_set_layouts++){
        size_t index = it_set_layouts - begin(_descriptor_set_layouts);
        for(size_t i = 0; i < layouts.size(); i += _nb_descriptor_set_by_image){
            layouts[i + index] = *it_set_layouts; // We pass from the first A to the second A
        }
    }
    vk::DescriptorSetAllocateInfo allo_info{};
    allo_info.descriptorPool = *_descriptor_pool;
    allo_info.descriptorSetCount = layouts.size();
    allo_info.pSetLayouts = layouts.data();

    _descriptor_sets.resize(layouts.size());
    checkError(
            _context.get_device().allocateDescriptorSets(&allo_info, _descriptor_sets.data()),
            "Failed to allocate descriptor set"
    );
}

void InitVulkan::update_descriptor_set(int first_descriptor_set_index, int binding, const buffer::image2d &image,
                                       const image::sampler &sampler) {
    /*
   * We use one descriptor set layout by image of the swap chain,
   * but for using multiple set layout, we store them as follow:
   * |A|B|A|B|A|B|
   * where A and B are different descriptor set layout
   *
   */
    std::vector<vk::WriteDescriptorSet> write_sets(_swapChainImageViews.size());
    std::vector<vk::DescriptorImageInfo> image_infos(_swapChainImageViews.size());
    auto it_descriptor_set = begin(_descriptor_sets) + first_descriptor_set_index;
    auto it_write_sets = begin(write_sets);
    auto it_image_infos = begin(image_infos);
   for(size_t i = 0; i < _swapChainImageViews.size(); i++){
       it_image_infos->imageLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
       it_image_infos->imageView = *image.get_image_view();
       it_image_infos->sampler = sampler;

        it_write_sets->dstSet = *it_descriptor_set;
        it_write_sets->dstBinding = binding; //this is a bug
        it_write_sets->dstArrayElement = 0 ;//that too
        it_write_sets->descriptorType= vk::DescriptorType ::eCombinedImageSampler;
        it_write_sets->descriptorCount = 1;
        it_write_sets->pImageInfo = &*it_image_infos;
        it_write_sets->pTexelBufferView = nullptr;

        it_write_sets++;
        it_image_infos++;
        it_descriptor_set += _nb_descriptor_set_by_image;
        /*
         *  |A|B|A|B|A|B| we pass from A to the other A
         * */
    }
    _context.get_device().updateDescriptorSets(write_sets.size(),
                                               write_sets.data(), 0, nullptr);
}
