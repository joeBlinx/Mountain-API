//
// Created by joe on 05/08/18.
//

#include "../include/initVulkan.hpp"
#include "../include/log.hpp"
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cstring>
#include <set>
#include <algorithm>
#include "../include/utils.hpp"
#include <array>
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
	createSwapChain();
	createImageViews();
	createRenderPass();
	createPipelineLayout();
	createGraphicsPipeline();
	createFrameBuffers();
	createCommandPool();
	createCommandBuffers();
	createSemaphores();
}

void InitVulkan::loop() {

	while (!glfwWindowShouldClose(_window)) {
		glfwPollEvents();
		drawFrame();
	}
	vkDeviceWaitIdle(_device);
}
void InitVulkan::drawFrame()
{
	uint32_t imageIndex;
	vkAcquireNextImageKHR(_device, _swapchain, std::numeric_limits<uint64_t>::max(), _imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { _imageAvailableSemaphore };

	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &_commandBuffers[imageIndex];

	VkSemaphore signalSemaphores[] = { _renderFinishedSemaphore };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	checkError(vkQueueSubmit(_graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE),
		"failed to submit draw command buffer!");

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = { _swapchain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr; // Optional
	vkQueuePresentKHR(_presentQueue, &presentInfo);

	vkQueueWaitIdle(_presentQueue);

}
namespace{
void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
	auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
	if (func != nullptr) {
		func(instance, callback, pAllocator);
	}
}
}
InitVulkan::~InitVulkan() {

	vkDestroySemaphore(_device, _renderFinishedSemaphore, nullptr);
	vkDestroySemaphore(_device, _imageAvailableSemaphore, nullptr);
	vkDestroyCommandPool(_device, _commandPool, nullptr);
	for (auto &framebuffer : _swapchainFrameBuffer) {
		vkDestroyFramebuffer(_device, framebuffer, nullptr);
	}
	vkDestroyPipeline(_device, _graphicsPipeline, nullptr);
	vkDestroyPipelineLayout(_device, _pipelineLayout, nullptr);
	vkDestroyRenderPass(_device, _renderpass, nullptr);
	for (auto& imageView : _swapChainImageViews) {
		vkDestroyImageView(_device, imageView, nullptr);
	}
	vkDestroySwapchainKHR(_device, _swapchain, nullptr);
	vkDestroyDevice(_device, nullptr);
	if(_enableValidationLayer){
		DestroyDebugReportCallbackEXT(_instance, _callback, nullptr);
	}
	vkDestroySurfaceKHR(_instance, _surface, nullptr);
	vkDestroyInstance(_instance, nullptr);
	
	glfwDestroyWindow(_window);
	glfwTerminate();
}

void errorGLFW([[maybe_unused]] int error, const char * msg){
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
namespace{
VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
	auto func = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pCallback);
	} else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
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

bool InitVulkan::checkDeviceExtensionSupport(VkPhysicalDevice device)
{
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string_view> requiredExtensions(_devicesExtension.begin(), _devicesExtension.end());

	for (auto const & extension : availableExtensions)
	{
		requiredExtensions.erase(extension.extensionName);
	}
	return requiredExtensions.empty();

}
bool InitVulkan::isDeviceSuitable(VkPhysicalDevice device) {
	QueueFamilyIndices indices = findQueueFamilies(device);

	bool extensionSupported = checkDeviceExtensionSupport(device);
	bool swapChainAdequate = false;
	if (extensionSupported) {
		SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
		swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
	}
	return indices.isComplete() && extensionSupported && swapChainAdequate;
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
		if(queueFamily.queueCount > 0 && presentSupport){
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
		queueInfo.queueFamilyIndex = static_cast<uint32_t>(queue);
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
	info.queueCreateInfoCount = (uint32_t)queueInfos.size();
	info .pEnabledFeatures = &features;
	info.enabledExtensionCount = static_cast<uint32_t>(_devicesExtension.size());
	info.ppEnabledExtensionNames = _devicesExtension.data();
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

SwapChainSupportDetails InitVulkan::querySwapChainSupport(VkPhysicalDevice device)
{
	SwapChainSupportDetails details;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, _surface, &details.capabilities);
	
	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, _surface, &formatCount, nullptr);

	if (formatCount != 0) {
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, _surface, &formatCount, details.formats.data());
	}

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, _surface, &presentModeCount, nullptr);

	if (presentModeCount != 0) {
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, _surface, &presentModeCount, details.presentModes.data());
	}


	return details;
}
VkSurfaceFormatKHR InitVulkan::chooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR> const & availableFormats)
{
	if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
		return { VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
	}

	for (const auto& availableFormat : availableFormats) {
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat;
		}
	}

	return availableFormats[0];
}

VkPresentModeKHR InitVulkan::chooseSwapPresentMode(std::vector<VkPresentModeKHR> const & availablePresentModes)
{
	VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

	for (const auto& availablePresentMode : availablePresentModes) {
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return availablePresentMode;
		}
		else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
			bestMode = availablePresentMode;
		}
	}

	return bestMode;
}
VkExtent2D InitVulkan::chooseSwapExtent(VkSurfaceCapabilitiesKHR const& capabilities)
{
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		return capabilities.currentExtent;
	}
	else {
		VkExtent2D actualExtent{ (uint32_t)_width, (uint32_t)_height };

		actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
		actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

		return actualExtent;
	}
}

void InitVulkan::createSwapChain()
{
	SwapChainSupportDetails swapChainSupport = querySwapChainSupport(_physicalDevice);

	VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
	VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);
	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = _surface;
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; // can change

	QueueFamilyIndices indices = findQueueFamilies(_physicalDevice);
	uint32_t queueFamilyIndices[] = { static_cast<uint32_t>(indices.graphicsFamily),
								   static_cast<uint32_t>(indices.presentFamily) };

	if (indices.graphicsFamily != indices.presentFamily) { 
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT; // one queue for all
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else {
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; // one queue for each mode, graphics, present
		createInfo.queueFamilyIndexCount = 0; // Optional
		createInfo.pQueueFamilyIndices = nullptr; // Optional
	}
	createInfo.preTransform = swapChainSupport.capabilities.currentTransform; // specify transform apply to swap chain
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; // alpha with other window
	createInfo.presentMode = presentMode; 
	createInfo.clipped = VK_TRUE; // don't care about color pixel in other window 
	createInfo.oldSwapchain = VK_NULL_HANDLE; // no old swap chain..for now 

	checkError(vkCreateSwapchainKHR(_device, &createInfo, nullptr, &_swapchain),
		"unable to create swapchain");

	vkGetSwapchainImagesKHR(_device, _swapchain, &imageCount, nullptr); //get the number of image the swapchain can handle
	_swapChainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(_device, _swapchain, &imageCount, _swapChainImages.data());

	_swapChainImageFormat = surfaceFormat.format;
	_swapChainExtent = extent;
	
}
void InitVulkan::createImageViews()
{
	_swapChainImageViews.resize(_swapChainImages.size());
	for (size_t i = 0; i < _swapChainImageViews.size(); i++)
	{
		VkImageViewCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = _swapChainImages[i];
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = _swapChainImageFormat;
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;
		checkError(
			vkCreateImageView(_device, &createInfo, nullptr, &_swapChainImageViews[i]),
				"unable to create Image View"
			);
	}
}


VkShaderModule InitVulkan::createShaderModule(std::vector<char> const & code)
{ // RAII possible
	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = (uint32_t*)code.data();
	VkShaderModule module;
	checkError(vkCreateShaderModule(_device, &createInfo, nullptr, &module),
		"failed to create Shader");

	return module;

}
VkPipelineShaderStageCreateInfo createShaderInfo(VkShaderModule & module, VkShaderStageFlagBits type)
{
	VkPipelineShaderStageCreateInfo info{};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	info.stage = type;
	info.module = module;
	info.pName = "main";
	return info;
}
VkPipelineInputAssemblyStateCreateInfo createAssembly(VkPrimitiveTopology topology)
{	//function needed
	VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = topology; // 3 vertices, one triangle
	inputAssembly.primitiveRestartEnable = VK_FALSE;
	return inputAssembly;

}
VkPipelineViewportStateCreateInfo createViewportPipeline(VkExtent2D const & swapchainExtent)
{

	//*********VIEW PORT*************
	static VkViewport viewport = {};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float)swapchainExtent.width;
	viewport.height = (float)swapchainExtent.height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	static VkRect2D scissor = {};
	scissor.offset = { 0, 0 };
	scissor.extent = swapchainExtent;

	VkPipelineViewportStateCreateInfo viewportState = {};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;

	return viewportState;
}
//need parameter in further modification
VkPipelineRasterizationStateCreateInfo createRasterizer()
{
	VkPipelineRasterizationStateCreateInfo rasterizer  {};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;
	rasterizer.depthBiasConstantFactor = 0.0f; // Optional
	rasterizer.depthBiasClamp = 0.0f; // Optional
	rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

	return rasterizer;
}
//need parameter in further modification
VkPipelineMultisampleStateCreateInfo createMultisampling()
{
	VkPipelineMultisampleStateCreateInfo multisampling {};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	multisampling.minSampleShading = 1.0f; // Optional
	multisampling.pSampleMask = nullptr; // Optional
	multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
	multisampling.alphaToOneEnable = VK_FALSE; // Optional

	return multisampling;
}
VkPipelineColorBlendAttachmentState createColorBlendAttachement()
{
	VkPipelineColorBlendAttachmentState colorBlendAttachment{};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;
	colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
	colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
	colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
	colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
	colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
	colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional
	return colorBlendAttachment;
}
VkPipelineColorBlendStateCreateInfo createColorBlendState(VkPipelineColorBlendAttachmentState & colorBlend)
{
	VkPipelineColorBlendStateCreateInfo colorBlending = {};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlend;
	colorBlending.blendConstants[0] = 0.0f; // Optional
	colorBlending.blendConstants[1] = 0.0f; // Optional
	colorBlending.blendConstants[2] = 0.0f; // Optional
	colorBlending.blendConstants[3] = 0.0f; // Optional

	return colorBlending;
}
void InitVulkan::createPipelineLayout() // lot of parameter
{
	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 0; // Optional
	pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
	pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
	pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

	checkError (vkCreatePipelineLayout(_device, &pipelineLayoutInfo, nullptr, &_pipelineLayout)
		,"failed to create pipeline layout!");
	
}
void InitVulkan::createGraphicsPipeline()
{
	std::vector<char> vertex = utils::readFile("trianglevert.spv");
	std::vector<char> fragment = utils::readFile("trianglefrag.spv");

	VkShaderModule vertexModule = createShaderModule(vertex);
	VkShaderModule fragmentModule = createShaderModule(fragment);

	VkPipelineShaderStageCreateInfo pipelineVertex = createShaderInfo(vertexModule,
		VK_SHADER_STAGE_VERTEX_BIT);
	VkPipelineShaderStageCreateInfo pipelineFrag = createShaderInfo(fragmentModule,
		VK_SHADER_STAGE_FRAGMENT_BIT);

	std::vector<VkPipelineShaderStageCreateInfo> shaderStage{ pipelineVertex,pipelineFrag };

	// vertex Input defintion -> in function ?
	VkPipelineVertexInputStateCreateInfo vertexInput{};
	vertexInput.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInput.vertexBindingDescriptionCount = 0; // no vertex buffer
	vertexInput.pVertexBindingDescriptions = nullptr; // Optional
	vertexInput.vertexAttributeDescriptionCount = 0; // no attribute
	vertexInput.pVertexAttributeDescriptions = nullptr; // Optional


	// define the topology the vertices  and what kind of geometry
	
	VkPipelineInputAssemblyStateCreateInfo inputAssembly = createAssembly(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);

	VkPipelineViewportStateCreateInfo viewportState = createViewportPipeline(_swapChainExtent);

	VkPipelineRasterizationStateCreateInfo rasterizer = createRasterizer();
	VkPipelineMultisampleStateCreateInfo multisampling = createMultisampling();

	// DEPTH AND STENCIL

	// COLOR
	VkPipelineColorBlendAttachmentState colorBlendAttachement = createColorBlendAttachement();
	VkPipelineColorBlendStateCreateInfo colorBlending = createColorBlendState(colorBlendAttachement);

	std::array shaderStages{ pipelineVertex, pipelineFrag };

	/**can be factorised in function
	*/
	VkGraphicsPipelineCreateInfo pipelineInfo  {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = shaderStages.size();
	pipelineInfo.pStages = shaderStages.data();

	pipelineInfo.pVertexInputState = &vertexInput;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pDepthStencilState = nullptr; // Optional nostencil for now
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.pDynamicState = nullptr; // Optional
	pipelineInfo.layout = _pipelineLayout;
	pipelineInfo.renderPass = _renderpass;
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
	pipelineInfo.basePipelineIndex = -1; // Optional
	checkError(vkCreateGraphicsPipelines(_device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &_graphicsPipeline)
		, "failed to create graphics pipeline!"
	);

	vkDestroyShaderModule(_device, fragmentModule, nullptr);
	vkDestroyShaderModule(_device, vertexModule, nullptr);

}
// some parameter
void InitVulkan::createRenderPass()
{
	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = _swapChainImageFormat;
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef = {};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	VkSubpassDependency dependency = {};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = 0;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	renderPassInfo.dependencyCount = 1;
	renderPassInfo.pDependencies = &dependency;


	checkError(vkCreateRenderPass(_device, &renderPassInfo, nullptr, &_renderpass), 
		"failed to create render pass!");
	
}

//need parameter
void InitVulkan::createFrameBuffers()
{
	_swapchainFrameBuffer.resize(_swapChainImageViews.size());
	for (size_t i = 0; i < _swapChainImageViews.size(); i++)
	{
		VkImageView attachments[] = {
			_swapChainImageViews[i]
		};

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = _renderpass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = _swapChainExtent.width;
		framebufferInfo.height = _swapChainExtent.height;
		framebufferInfo.layers = 1;

		checkError (vkCreateFramebuffer(_device, &framebufferInfo, nullptr, &_swapchainFrameBuffer[i]),
			"failed to create framebuffer!");
		
	}

}
void InitVulkan::createCommandPool()
{
	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = _indices.graphicsFamily;
	poolInfo.flags = 0; // Optional need parameter

	checkError (vkCreateCommandPool(_device, &poolInfo, nullptr, &_commandPool),
		"failed to create command pool!");
	
}
//unique by software
void InitVulkan::createCommandBuffers()
{
	_commandBuffers.resize(_swapchainFrameBuffer.size());
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = _commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)_commandBuffers.size();

	checkError (vkAllocateCommandBuffers(_device, &allocInfo, _commandBuffers.data()),
		"failed to allocate command buffers!");

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

		VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		vkCmdBindPipeline(_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, _graphicsPipeline); // bind the pipeline
		vkCmdDraw(_commandBuffers[i], 3, 1, 0, 0); // draw buffer

		vkCmdEndRenderPass(_commandBuffers[i]);
		checkError(vkEndCommandBuffer(_commandBuffers[i]),
			"failed to record command buffer!");
		
	}

}
void InitVulkan::createSemaphores()
{
	VkSemaphoreCreateInfo semaphoreInfo {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	checkError(vkCreateSemaphore(_device, &semaphoreInfo, nullptr, &_imageAvailableSemaphore),
			"failed to create semaphores!");

	checkError(vkCreateSemaphore(_device, &semaphoreInfo, nullptr, &_renderFinishedSemaphore),
		"failed to create semaphores!");
		
	
}
