#include "context.hpp"	
#include <GLFW/glfw3.h>
#include "utils/utils.hpp"
#include <string_view>
#include "utils/log.hpp"
#include <iostream>
#include <cstring>
#include <string_view>
#include <set>
Context::SwapChainSupportDetails query_swap_chain_support(vk::PhysicalDevice const& device, VkSurfaceKHR surface);
Context::QueueFamilyIndices find_queue_families(vk::PhysicalDevice const& device, VkSurfaceKHR surface, vk::QueueFlagBits queue_flag);

Context::Context(int width, int height, std::string_view title, std::vector<const char*> const& devicesExtension)
:_width(width),
_height(height)
{
	initWindow(title);
	createInstance(title);
	createSurface();
	setUpDebugCallBack();

	auto queue_flag = vk::QueueFlagBits::eGraphics;

	auto const& surface = get_vk_surface();
	pick_up_physical_device(get_vk_instance(), queue_flag, devicesExtension,surface);

	_swap_chain_details = query_swap_chain_support(_physical_device, surface);
	_indices = find_queue_families(_physical_device, surface, queue_flag);

	create_logical_device(devicesExtension, _validationLayers);
    create_command_pool();
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
std::vector<char const *> Context::getRequiredExtension() {

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

Context::~Context()
{

	 _device.destroy(_command_pool);
    _device.destroy();
	if constexpr (_enableValidationLayer) {
		DestroyDebugReportCallbackEXT(_instance, _callback, nullptr);
	}
	_instance.destroy(_surface);
	_instance.destroy();
	glfwDestroyWindow(_window);
	glfwTerminate();
}

void Context::initWindow(std::string_view title) {

	glfwInit();
	glfwSetErrorCallback(errorGLFW);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	_window = glfwCreateWindow(_width, _height, title.data(), nullptr, nullptr);
	if (!_window) {
		utils::printFatalError("unable to Create window");
	}
}
bool Context::checkValidationLayerSupport() {

	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	std::vector<VkLayerProperties> availableLayer(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayer.data());
	bool layerFound = false;
	for (auto layer : _validationLayers) {
		for (auto available : availableLayer) {
		    std::string test(available.layerName);
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
void Context::setUpDebugCallBack() {

	if constexpr (!_enableValidationLayer) return;

	VkDebugReportCallbackCreateInfoEXT info{};
	info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	info.pfnCallback = debugCallback;
	info.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;

	checkError(CreateDebugReportCallbackEXT(_instance, &info, nullptr, &_callback),
	"Failed to set up debug _callback");
}
void Context::createInstance(std::string_view title)
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

void Context::createSurface() {
	checkError(glfwCreateWindowSurface(_instance,
		_window, nullptr, &_surface),
		"unable to create surface");
}


Context::QueueFamilyIndices find_queue_families(vk::PhysicalDevice const& device, VkSurfaceKHR surface, vk::QueueFlagBits queue_flag)
{
	Context::QueueFamilyIndices indices;
	auto queueFamilies = device.getQueueFamilyProperties();
	uint32_t i = 0;

	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & queue_flag) {
			indices.graphics_family = i;
		}

		vk::Bool32 presentSupport = device.getSurfaceSupportKHR(i, surface);
		if(queueFamily.queueCount > 0 && presentSupport){
			indices.present_family = i;
		}
		if (indices.isComplete()) {
			break;

		}

		i++;
	}

	return indices;
}
Context::SwapChainSupportDetails query_swap_chain_support(vk::PhysicalDevice const& device, VkSurfaceKHR surface)
{
	Context::SwapChainSupportDetails details;
	details.capabilities = device.getSurfaceCapabilitiesKHR(surface);
	details.formats = device.getSurfaceFormatsKHR(surface);
	details.presentModes = device.getSurfacePresentModesKHR(surface);

	return details;
}
bool check_device_extension_support(vk::PhysicalDevice const& device, std::vector<const char *> const& devicesExtension)
{

	auto availableExtensions = device.enumerateDeviceExtensionProperties();
	std::set<std::string_view> requiredExtensions {devicesExtension.begin(), devicesExtension.end()};

	for (auto const & extension : availableExtensions)
	{
		requiredExtensions.erase(std::string_view(extension.extensionName));
	}
	return requiredExtensions.empty();
}

bool is_device_suitable(vk::PhysicalDevice const& device, vk::QueueFlagBits queue_flag,
		std::vector<const char *> const& devicesExtension, VkSurfaceKHR surface)
{
	Context::QueueFamilyIndices indices = find_queue_families(device, surface, queue_flag);

	bool extensionSupported = check_device_extension_support(device, devicesExtension);
	bool swapChainAdequate = false;
	if (extensionSupported) {
		Context::SwapChainSupportDetails swapChainSupport = query_swap_chain_support(device, surface);
		swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
	}
	return indices.isComplete() && extensionSupported && swapChainAdequate;
}


void Context::pick_up_physical_device(vk::Instance instance, vk::QueueFlagBits queue_flag, std::vector<const char *> const &devicesExtension,
									 VkSurfaceKHR surface) {
	
	auto physicalDevices = instance.enumeratePhysicalDevices();
	if(!physicalDevices.size()){
		utils::printFatalError("failed to find gpu with vulkan support");
	}

	for(auto device : physicalDevices){
		if(is_device_suitable(device, queue_flag, devicesExtension, surface)){
			_physical_device = device;
			return;
		}
	}

	utils::printFatalError("no suitable GPU found");
}

void Context::create_logical_device(std::vector<char const *> const &devicesExtension,
								   std::vector<const char *> const &validationLayers) {

	//specify the queue
	std::vector<vk::DeviceQueueCreateInfo> queueInfos;
	std::set<int> uniqueQueueFamilies{_indices.graphics_family, _indices.present_family};
	for (auto queue : uniqueQueueFamilies) {
		vk::DeviceQueueCreateInfo queueInfo{};
		queueInfo.queueFamilyIndex = static_cast<uint32_t>(queue);
		queueInfo.queueCount = QueueFamilyIndices::number_queue;
		float queuePriority = 1.0f;
		queueInfo.pQueuePriorities = &queuePriority;
		queueInfos.push_back(queueInfo);
	}
	//feature required
	vk::PhysicalDeviceFeatures features{};

	vk::DeviceCreateInfo info{};
	info.setPQueueCreateInfos(queueInfos.data());
	info.queueCreateInfoCount = (uint32_t)queueInfos.size();
	info .pEnabledFeatures = &features;
	info.enabledExtensionCount = static_cast<uint32_t>(devicesExtension.size());
	info.ppEnabledExtensionNames = devicesExtension.data();
	if constexpr(utils::debug){
		info.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		info.ppEnabledLayerNames = validationLayers.data();
	}

	_device = _physical_device.createDevice(info),
	_graphics_queue = _device.getQueue(_indices.graphics_family, 0);
	_present_queue = _device.getQueue(_indices.present_family, 0);
}
void Context::create_command_pool(){
	vk::CommandPoolCreateInfo pool_info{
		vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
		static_cast<uint32_t>(_indices.graphics_family)
	};
	_command_pool = _device.createCommandPool(pool_info);
}

std::pair<vk::UniqueBuffer,
		vk::UniqueDeviceMemory> Context::create_buffer_and_memory(vk::DeviceSize const& size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags properties) const{
	vk::BufferCreateInfo buffer_info{
		{},
		size, 
		usage,
		vk::SharingMode::eExclusive
	};
	vk::UniqueBuffer buffer = _device.createBufferUnique(buffer_info);
	
	vk::MemoryRequirements mem_requirement;
	_device.getBufferMemoryRequirements(*buffer, &mem_requirement);
	auto device_memory = create_device_memory(mem_requirement, properties);
	_device.bindBufferMemory(*buffer, *device_memory, 0);
	return {
		std::move(buffer), 
		std::move(device_memory)
		};
}
vk::UniqueDeviceMemory Context::create_device_memory(vk::MemoryRequirements const& mem_requirements, vk::MemoryPropertyFlags properties) const{
	auto mem_properties = _physical_device.getMemoryProperties();

	auto find_memory_type = [&mem_properties, type_filter = mem_requirements.memoryTypeBits, &properties]() {
		for (uint32_t i =0; i < mem_properties.memoryTypeCount ;i++){
			 if ((type_filter & (1 << i)) && (mem_properties.memoryTypes[i].propertyFlags & properties) == properties) {
      		  	return i;
    		}
		}
		utils::printFatalError("failed to find suitable memory type!");
		return 0u;
	};
	return _device.allocateMemoryUnique(
		vk::MemoryAllocateInfo(
			mem_requirements.size,
			find_memory_type()
		)
	);
}

void Context::copy_buffer(vk::UniqueBuffer& destination, vk::UniqueBuffer const& source, vk::DeviceSize const& size) const{
	vk::CommandBufferAllocateInfo alloc_info{
		_command_pool,
		vk::CommandBufferLevel::ePrimary,
		1
	};
	auto command_buffers = _device.allocateCommandBuffersUnique(alloc_info);
	vk::CommandBufferBeginInfo begin_info{
		vk::CommandBufferUsageFlagBits::eOneTimeSubmit
	};
	auto command_buffer = std::move(command_buffers[0]);
	command_buffer->begin(begin_info);
	vk::BufferCopy buffer_copy{
	    0,
	    0,
	    size
	};
	command_buffer->copyBuffer(*source, *destination, 1, &buffer_copy);
	command_buffer->end();

	vk::SubmitInfo submit_info;
	submit_info.commandBufferCount = 1;
	submit_info.pCommandBuffers = &command_buffer.get();
	_graphics_queue.submit(1, &submit_info, {});
	_graphics_queue.waitIdle();

}
