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
struct GraphicsPipeline;
struct InitVulkan {

	InitVulkan(const Context &context, const SwapChain &swap_chain, RenderPass const &renderpass,
               GraphicsPipeline const &graphics_pipeline, const std::vector<buffer::vertex> &buffers);
	void loop(GLFWwindow *window);
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
	vk::Pipeline _graphicsPipeline;
	std::vector<vk::Framebuffer> _swapchainFrameBuffer;
	vk::CommandPool const& _commandPool;
	std::vector<vk::CommandBuffer> _commandBuffers;
	vk::Queue  _graphicsQueue;

	vk::Queue  _presentQueue;
	vk::RenderPass _renderpass;

	vk::Semaphore _imageAvailableSemaphore;
	vk::Semaphore _renderFinishedSemaphore;
	
	void createCommandBuffers(const std::vector<buffer::vertex> &buffer);
	void drawFrame();
	void createSemaphores();

	void createFrameBuffers();
};




#endif //SANDBOX_INITVULKAN_HPP
