//
// Created by joe on 05/08/18.
//

#ifndef SANDBOX_INITVULKAN_HPP
#define SANDBOX_INITVULKAN_HPP

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>

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
	void loop();
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
	GLFWwindow *_window;
	VkInstance _instance;
	VkSurfaceKHR _surface;
	VkDebugReportCallbackEXT _callback;
	VkPhysicalDevice _physicalDevice = 	VK_NULL_HANDLE;
	VkDevice _device;
	QueueFamilyIndices _indices;

	VkQueue  _graphicsQueue;
	VkQueue  _presentQueue;

	void initWindow();
	bool checkValidationLayerSupport();
	void createInstance();
	void createSurface();

	std::vector<char const * > getRequiredExtension();
	void setUpDebugCallBack();
	bool isDeviceSuitable(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	void pickUpPhysicalDevice();
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR> const & availableFormat);
	VkPresentModeKHR chooseSwapPresentMode(std::vector<VkPresentModeKHR> const & availablePresentModes);
	void createLogicalDevice();
};


#endif //SANDBOX_INITVULKAN_HPP
