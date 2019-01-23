//
// Created by joe on 05/08/18.
//

#include "initVulkan.hpp"
#include "log.hpp"
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cstring>
#include <set>
#include "utils.hpp"

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t obj,
		size_t location,
		int32_t code,
		const char* layerPrefix,
		const char* msg,
		void* userData) {

	std::cerr << "validation layer: " << msg << std::endl;

	return VK_FALSE;
}
bool InitVulkan::checkValidationLayerSupport() {
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayer(layerCount);

	vkEnumerateInstanceLayerProperties(&layerCount, availableLayer.data());

	bool layerFound = false;
	for (auto layer : validationLayers) {
		for (auto available : availableLayer) {
			if (!strcmp(layer, available.layerName)) {
				layerFound = true;
				break;
			}
		}
	}
	return layerFound;

}

InitVulkan::InitVulkan(int width, int height) : _width(width),
												_height(height) {
	initWindow();
	createInstance();
	createSurface();
	setUpDebugCallBack();
	pickUpPhysicalDevice();
	createLogicalDevice();
}

void InitVulkan::loop() {

//	while(1){
//
//	}
}
void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
	auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
	if (func != nullptr) {
		func(instance, callback, pAllocator);
	}
}
InitVulkan::~InitVulkan() {

	vkDestroyDevice(_device, nullptr);
	if(_enableValidationLayer){
		DestroyDebugReportCallbackEXT(_instance, _callback, nullptr);
	}
	vkDestroySurfaceKHR(_instance, _surface, nullptr);
	vkDestroyInstance(_instance, nullptr);
	glfwDestroyWindow(_window);
	glfwTerminate();
}

void errorGLFW(int error, const char * msg){
	utils::printError(msg);
}
void InitVulkan::initWindow() {
	glfwInit();
	glfwSetErrorCallback(errorGLFW);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	_window = glfwCreateWindow(_width, _height, "Vulkan", nullptr, nullptr);
	if(!_window){
		utils::printFatalError("unable to Create window");
	}
}

void InitVulkan::createInstance() {

	if (!checkValidationLayerSupport() && _enableValidationLayer) {
		utils::printFatalError("validation layer requested but not available");
	}

	VkApplicationInfo info{};
	info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	info.pApplicationName = "Sand Box";
	info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	info.pEngineName = "No Engine;";
	info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	info.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo instanceinfo{};
	instanceinfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceinfo.pApplicationInfo = &info;

	auto extensions = getRequiredExtension();
	instanceinfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	instanceinfo.ppEnabledExtensionNames = extensions.data();

	instanceinfo.enabledLayerCount = 0;

	if (_enableValidationLayer) {
		instanceinfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		instanceinfo.ppEnabledLayerNames = validationLayers.data();
	}

	checkError(vkCreateInstance(&instanceinfo, nullptr, &_instance),
			   "failed to create Instance");

	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> extensionsProperties(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionsProperties.data());
	std::cout << "available extensions:" << std::endl;

	for (const auto &extension : extensionsProperties) {
		std::cout << "\t" << extension.extensionName << std::endl;
	}
}

std::vector<char const *> InitVulkan::getRequiredExtension() {

	uint32_t glfwExtensionCount = 0;
	const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (_enableValidationLayer) {
		extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	}

	return extensions;
}

VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
	auto func = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pCallback);
	} else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void InitVulkan::setUpDebugCallBack() {

	if(!_enableValidationLayer) return;

	VkDebugReportCallbackCreateInfoEXT info{};
	info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	info.pfnCallback = debugCallback;
	info.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;

	checkError(CreateDebugReportCallbackEXT(_instance, &info, nullptr, &_callback),
	"Failed to set up debug _callback");
}

void InitVulkan::pickUpPhysicalDevice() {
	uint32_t count ;
	vkEnumeratePhysicalDevices(_instance, &count, nullptr);
	if(!count){
		utils::printFatalError("failed to find gpu with vulkan support");
	}

	std::vector<VkPhysicalDevice > physicalDevices(count);
	vkEnumeratePhysicalDevices(_instance, &count, physicalDevices.data());

	for(auto device : physicalDevices){
		if(isDeviceSuitable(device)){
			_physicalDevice = device;
			return;
		}
	}

	utils::printFatalError("not suitable GPU found");


}

bool InitVulkan::isDeviceSuitable(VkPhysicalDevice device) {
	QueueFamilyIndices indices = findQueueFamilies(device);


	return indices.isComplete();
}

QueueFamilyIndices InitVulkan::findQueueFamilies(VkPhysicalDevice device) {
	QueueFamilyIndices indices;
	uint32_t queueFamilyCount = 0;

	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
	uint32_t i = 0;

	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}
		 
		VkBool32 presentSupport  = VK_FALSE;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, _surface, &presentSupport);
		if(queueFamily.queueCount >= 0 && presentSupport){
			indices.presentFamily = i;
		}
		if (indices.isComplete()) {
			_indices = indices;
			break;
		}

		i++;
	}

	return indices;
}

void InitVulkan::createLogicalDevice() {


	//specify the queue
	std::vector<VkDeviceQueueCreateInfo> queueInfos;
	std::set<int> uniqueQueueFamilies{_indices.graphicsFamily, _indices.presentFamily};
	for (auto queue : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueInfo{};
		queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueInfo.queueFamilyIndex = static_cast<uint32_t>(_indices.graphicsFamily);
		queueInfo.queueCount = QueueFamilyIndices::numberQueue;
		float queuePriority = 1.0f;
		queueInfo.pQueuePriorities = &queuePriority;
		queueInfos.push_back(queueInfo);
	}
	//feature required
	VkPhysicalDeviceFeatures features{};

	VkDeviceCreateInfo info{};
	info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	info.pQueueCreateInfos = queueInfos.data();
	info.queueCreateInfoCount = queueInfos.size();
	info .pEnabledFeatures = &features;
	info.enabledExtensionCount = 0;
	if(_enableValidationLayer){
		info.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		info.ppEnabledLayerNames = validationLayers.data();
	}

	checkError(vkCreateDevice(_physicalDevice,
			&info, nullptr, &_device),
					"unable to create Logical device");

	vkGetDeviceQueue(_device, _indices.graphicsFamily, 0, &_graphicsQueue);
	vkGetDeviceQueue(_device, _indices.presentFamily, 0, &_presentQueue);
}

void InitVulkan::createSurface() {
	checkError(glfwCreateWindowSurface(_instance,
			_window, nullptr, &_surface),
					"unable to create surface");
}



























