#include "basicInit.hpp"	
#include <GLFW/glfw3.h>
#include "utils.hpp"
#include <string_view>
#include "log.hpp"
#include <iostream>

BasicInit::BasicInit(unsigned width, unsigned height, std::string_view title)
:_width(width),
_height(height)
{
	initWindow(title);
	createInstance(title);
}
namespace {
	void errorGLFW(int error, const char * msg) {
		utils::printError(msg);
	}
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

void BasicInit::createInstance(std::string_view title)
{
	if (!checkValidationLayerSupport() && _enableValidationLayer) {
		utils::printFatalError("validation layer requested but not available");
	}

	VkApplicationInfo info{};
	info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	info.pApplicationName = title.data();
	info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	info.pEngineName = "No Engine";
	info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	info.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo instanceinfo{};
	instanceinfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceinfo.pApplicationInfo = &info;

	std::vector<const char *> extensions(getRequiredExtension());
	instanceinfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	instanceinfo.ppEnabledExtensionNames = extensions.data();

	instanceinfo.enabledLayerCount = 0;

	if constexpr(_enableValidationLayer) {
		instanceinfo.enabledLayerCount = static_cast<uint32_t>(_validationLayers.size());
		instanceinfo.ppEnabledLayerNames = _validationLayers.data();
	}

	checkError(vkCreateInstance(&instanceinfo, nullptr, &_instance),
		"failed to create Instance");

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



