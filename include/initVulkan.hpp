//
// Created by joe on 05/08/18.
//

#ifndef SANDBOX_INITVULKAN_HPP
#define SANDBOX_INITVULKAN_HPP

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "../sandbox_useful/device.hpp"

struct QueueFamilyIndices{
	static int constexpr numberQueue = 1;
	int graphicsFamily = -1;
	int presentFamily = -1;

	bool isComplete(){
		return graphicsFamily >=0  && presentFamily >= 0;
	}
};

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector <VkPresentModeKHR> presentModes;
};
struct InitVulkan {
	InitVulkan(int width, int height);
	InitVulkan(VkInstance instance, VkSurfaceKHR surface, VkDevice device, VkQueue graphics, VkQueue present,
			   VkPhysicalDevice physics, VkSwapchainKHR swap_chain, std::vector<VkImageView> const &image_views,
			   VkExtent2D extent, VkFormat format, Device::QueueFamilyIndices const &indices);
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
	VkInstance _instance;
	VkSurfaceKHR _surface;
	VkSwapchainKHR _swapchain;
	std::vector<VkImage> _swapChainImages;
	std::vector<VkImageView> _swapChainImageViews;
	VkFormat _swapChainImageFormat;
	VkExtent2D _swapChainExtent;
	VkPhysicalDevice _physicalDevice = 	VK_NULL_HANDLE;
	VkDevice _device;
	Device::QueueFamilyIndices _indices;
	VkPipelineLayout _pipelineLayout;
	VkRenderPass _renderpass;
	VkPipeline _graphicsPipeline;
	std::vector<VkFramebuffer> _swapchainFrameBuffer;
	VkCommandPool _commandPool;
	std::vector<VkCommandBuffer> _commandBuffers;

	VkQueue  _graphicsQueue;
	VkQueue  _presentQueue;

	VkSemaphore _imageAvailableSemaphore;
	VkSemaphore _renderFinishedSemaphore;


	VkShaderModule createShaderModule(std::vector<char> const & code);
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
