//
// Created by joe on 05/08/18.
//

#ifndef SANDBOX_INITVULKAN_HPP
#define SANDBOX_INITVULKAN_HPP

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include <sandbox_useful/swapChain.hpp>
#include <sandbox_useful/basicInit.hpp>
#include "sandbox_useful/device.hpp"

struct InitVulkan {
	InitVulkan(int width, int height);
	InitVulkan(const BasicInit &context, const Device &device, const SwapChain &swap_chain,
               Device::QueueFamilyIndices const &indices, vk::RenderPass renderpass);
	void loop(GLFWwindow *window);
	~InitVulkan();

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

	std::vector<vk::ImageView> _swapChainImageViews;
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
	void createGraphicsPipeline(); // multiple parameters but can surely be divide in some fucntions
	void createPipelineLayout(); // lot of parameter
	void createRenderPass();
	void createCommandPool();
	void createCommandBuffers();
	void drawFrame();
	void createSemaphores();

	void createFrameBuffers();
};


#endif //SANDBOX_INITVULKAN_HPP
