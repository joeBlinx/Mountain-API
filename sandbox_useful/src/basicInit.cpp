#include "basicInit.hpp"	
#include <GLFW/glfw3.h>
#include "utils/utils.hpp"
#include <string_view>
#include "utils/log.hpp"
#include <iostream>
#include <cstring>
BasicInit::BasicInit(int width, int height, std::string_view title)
:_width(width),
_height(height)
{
	initWindow(title);
	createInstance(title);
	createSurface();
	setUpDebugCallBack();
}

void errorGLFW([[maybe_unused]] int error, const char * msg) {
	utils::printError(msg);
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		[[maybe_unused]] VkDebugReportFlagsEXT flags,
		[[maybe_unused]] VkDebugReportObjectTypeEXT objType,
		[[maybe_unused]] uint64_t obj,
		[[maybe_unused]] size_t location,
		[[maybe_unused]] int32_t code,
		[[maybe_unused]] const char* layerPrefix,
		const char* msg,
		[[maybe_unused]] void* userData) {

	std::cerr << "validation layer: " << msg << std::endl;

	return VK_FALSE;
}
std::vector<char const *> BasicInit::getRequiredExtension() {

	uint32_t glfwExtensionCount = 0;
	const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (_enableValidationLayer) {
		extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	}

	return extensions;
}
void DestroyDebugReportCallbackEXT(vk::Instance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
	auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
	if (func != nullptr) {
		func(instance, callback, pAllocator);
	}
}

BasicInit::~BasicInit()
{

	if (_enableValidationLayer) {
		DestroyDebugReportCallbackEXT(_instance, _callback, nullptr);
	}
	vkDestroySurfaceKHR(_instance, _surface, nullptr);
	vkDestroyInstance(_instance, nullptr);
	glfwDestroyWindow(_window);
	glfwTerminate();
}

void BasicInit::initWindow(std::string_view title) {

	glfwInit();
	glfwSetErrorCallback(errorGLFW);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	_window = glfwCreateWindow(_width, _height, title.data(), nullptr, nullptr);
	if (!_window) {
		utils::printFatalError("unable to Create window");
	}
}
bool BasicInit::checkValidationLayerSupport() {

	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	std::vector<VkLayerProperties> availableLayer(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayer.data());
	bool layerFound = false;
	for (auto layer : _validationLayers) {
		for (auto available : availableLayer) {
			if (!strcmp(layer, available.layerName)) {
				layerFound = true;
				break;
			}
		}
	}
	return layerFound;

}
VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
	auto func = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pCallback);
	} else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}
void BasicInit::setUpDebugCallBack() {

	if constexpr (!_enableValidationLayer) return;

	VkDebugReportCallbackCreateInfoEXT info{};
	info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	info.pfnCallback = debugCallback;
	info.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;

	checkError(CreateDebugReportCallbackEXT(_instance, &info, nullptr, &_callback),
	"Failed to set up debug _callback");
}
void BasicInit::createInstance(std::string_view title)
{
	if (!checkValidationLayerSupport() && _enableValidationLayer) {
		utils::printFatalError("validation layer requested but not available");
	}

	vk::ApplicationInfo info{};
	info.pApplicationName = title.data();
	info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	info.pEngineName = "No Engine";
	info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	info.apiVersion = VK_API_VERSION_1_0;

	vk::InstanceCreateInfo instanceinfo{};
	instanceinfo.pApplicationInfo = &info;

	std::vector<const char *> extensions(getRequiredExtension());
	instanceinfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	instanceinfo.ppEnabledExtensionNames = extensions.data();

	instanceinfo.enabledLayerCount = 0;

	if constexpr(_enableValidationLayer) {
		instanceinfo.enabledLayerCount = static_cast<uint32_t>(_validationLayers.size());
		instanceinfo.ppEnabledLayerNames = _validationLayers.data();
	}
	_instance = vk::createInstance(instanceinfo); 
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> extensionsProperties(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionsProperties.data());

	if constexpr (_enableValidationLayer)
	{
		std::cout << "available extensions:" << std::endl;
		for (const auto &extension : extensionsProperties) {
			std::cout << "\t" << extension.extensionName << std::endl;
		}
	}
}

void BasicInit::createSurface() {
	checkError(glfwCreateWindowSurface(_instance,
		_window, nullptr, &_surface),
		"unable to create surface");
}



