//
// Created by joe on 05/08/18.
//

#ifndef SANDBOX_INITVULKAN_HPP
#define SANDBOX_INITVULKAN_HPP

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include "sandbox_useful/swapChain.hpp"
#include "sandbox_useful/context.hpp"
#include "sandbox_useful/renderpass/renderPass.hpp"
#include "utils/utils.hpp"
#include "sandbox_useful/buffer/vertex.hpp"
#include "sandbox_useful/buffer/vertex.hpp"
#include "graphics_pipeline.hpp"
#include <cstddef>
struct GraphicsPipeline;
struct InitVulkan {

	InitVulkan(const Context &context, const SwapChain &swap_chain, RenderPass const &renderpass);
	void loop(GLFWwindow *window);
    template <class T>
    void createCommandBuffers(T const& obj);
    void drawFrame();
    ~InitVulkan();

private:
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
	Context::QueueFamilyIndices _indices;
    std::vector<vk::Framebuffer> _swapchainFrameBuffer;
	vk::CommandPool const& _commandPool;
	std::vector<vk::CommandBuffer> _commandBuffers;
	vk::Queue  _graphicsQueue;

	vk::Queue  _presentQueue;
	vk::RenderPass _renderpass;

	vk::Semaphore _imageAvailableSemaphore;
	vk::Semaphore _renderFinishedSemaphore;


	void createSemaphores();

	void createFrameBuffers();

    void allocate_command_buffer();
};


template <class T>
void InitVulkan::createCommandBuffers(T const& obj)
{


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

        VkClearValue clearColor = { 0.5f, 0.5f, 0.5f, 1.0f };
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, obj.graphics_pipeline.get_pipeline()); // bind the pipeline
        auto& vertex_buffer = obj.vertices;
//        for(auto const& vertex_buffer : buffers){
            _commandBuffers[i].bindVertexBuffers(0, 1, &vertex_buffer.get_buffer(), std::vector<vk::DeviceSize>{0}.data());
            _commandBuffers[i].bindIndexBuffer(vertex_buffer.get_buffer(), vertex_buffer.get_indices_offset(), vk::IndexType::eUint16);
            for (auto const& value: obj.values) {
                for (auto const &push_constant_range : obj.graphics_pipeline.get_push_constant_ranges()) {
                    _commandBuffers[i].pushConstants(obj.graphics_pipeline.get_pipeline_layout(),
                                                     push_constant_range.stageFlags, push_constant_range.offset,
                                                     push_constant_range.size, (reinterpret_cast<std::byte const*>(&value)+push_constant_range.offset));
                }
                vkCmdDrawIndexed(_commandBuffers[i], vertex_buffer.get_indices_count(), 1, 0, 0, 0); // draw buffer
            }
//        }

        vkCmdEndRenderPass(_commandBuffers[i]);
        checkError(vkEndCommandBuffer(_commandBuffers[i]),
                   "failed to record command buffer!");

    }

}
#endif //SANDBOX_INITVULKAN_HPP
