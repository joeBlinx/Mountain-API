//
// Created by joe on 4/30/19.
//

#include <string_view>
#include "device.hpp"
#include <set>
#include "log.hpp"
#include "utils.hpp"

Device::QueueFamilyIndices find_queue_families(VkPhysicalDevice device, VkSurfaceKHR surface, VkQueueFlagBits queue_flag)
{
	Device::QueueFamilyIndices indices;
	uint32_t queueFamilyCount = 0;

	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
	uint32_t i = 0;

	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & queue_flag) {
			indices.graphics_family = i;
		}

		VkBool32 presentSupport  = VK_FALSE;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
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
Device::SwapChainSupportDetails query_swap_chain_support(VkPhysicalDevice device, VkSurfaceKHR surface)
{
	Device::SwapChainSupportDetails details;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

	if (formatCount != 0) {
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
	}

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

	if (presentModeCount != 0) {
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
	}


	return details;
}
bool check_device_extension_support(VkPhysicalDevice device, std::vector<const char *> const& devicesExtension)
{
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string_view> requiredExtensions {devicesExtension.begin(), devicesExtension.end()};

	for (auto const & extension : availableExtensions)
	{
		requiredExtensions.erase(extension.extensionName);
	}
	return requiredExtensions.empty();
}

bool is_device_suitable(VkPhysicalDevice device, VkQueueFlagBits queue_flag,
		std::vector<const char *> const& devicesExtension, VkSurfaceKHR surface)
{
	Device::QueueFamilyIndices indices = find_queue_families(device, surface, queue_flag);

	bool extensionSupported = check_device_extension_support(device, devicesExtension);
	bool swapChainAdequate = false;
	if (extensionSupported) {
		Device::SwapChainSupportDetails swapChainSupport = query_swap_chain_support(device, surface);
		swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
	}
	return indices.isComplete() && extensionSupported && swapChainAdequate;
}

Device::~Device() {
	vkDestroyDevice(_device, nullptr);
}

void Device::pick_up_physical_device(VkInstance instance, VkQueueFlagBits queue_flag, std::vector<const char *> const &devicesExtension,
									 VkSurfaceKHR surface) {
	uint32_t count ;
	vkEnumeratePhysicalDevices(instance, &count, nullptr);
	if(!count){
		utils::printFatalError("failed to find gpu with vulkan support");
	}

	std::vector<VkPhysicalDevice > physicalDevices(count);
	vkEnumeratePhysicalDevices(instance, &count, physicalDevices.data());

	for(auto device : physicalDevices){
		if(is_device_suitable(device, queue_flag, devicesExtension, surface)){
			_physical_device = device;
			return;
		}
	}

	utils::printFatalError("not suitable GPU found");
}

void Device::create_logical_device(std::vector<char const *> const &devicesExtension,
								   std::vector<const char *> const &validationLayers) {

	//specify the queue
	std::vector<VkDeviceQueueCreateInfo> queueInfos;
	std::set<int> uniqueQueueFamilies{_indices.graphics_family, _indices.present_family};
	for (auto queue : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueInfo{};
		queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueInfo.queueFamilyIndex = static_cast<uint32_t>(queue);
		queueInfo.queueCount = QueueFamilyIndices::number_queue;
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
	info.enabledExtensionCount = static_cast<uint32_t>(devicesExtension.size());
	info.ppEnabledExtensionNames = devicesExtension.data();
	if constexpr(utils::debug){
		info.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		info.ppEnabledLayerNames = validationLayers.data();
	}

	checkError(vkCreateDevice(_physical_device,
							  &info, nullptr, &_device),
			   "unable to create Logical device");

	vkGetDeviceQueue(_device, _indices.graphics_family, 0, &_graphics_queue);
	vkGetDeviceQueue(_device, _indices.present_family, 0, &_present_queue);
}

Device::Device(VkInstance instance, VkQueueFlagBits queue_flag, std::vector<const char *> const &devicesExtension,
			   VkSurfaceKHR surface, std::vector<const char *> const &validationLayers){
	pick_up_physical_device(instance, queue_flag, devicesExtension, surface);

	_swap_chain_details = query_swap_chain_support(_physical_device, surface);
	_indices = find_queue_families(_physical_device, surface, queue_flag);

	create_logical_device(devicesExtension, validationLayers);

}
