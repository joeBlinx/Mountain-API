//
// Created by joe on 4/30/19.
//

#include <string_view>
#include "device.hpp"
#include <set>
#include "log.hpp"
#include "utils.hpp"

Device::QueueFamilyIndices find_queue_families(vk::PhysicalDevice const& device, VkSurfaceKHR surface, vk::QueueFlagBits queue_flag)
{
	Device::QueueFamilyIndices indices;
	auto queueFamilies = device.getQueueFamilyProperties();
	uint32_t i = 0;

	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & queue_flag) {
			indices.graphics_family = i;
		}

		VkBool32 presentSupport = device.getSurfaceSupportKHR(i, surface);
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
Device::SwapChainSupportDetails query_swap_chain_support(vk::PhysicalDevice const& device, VkSurfaceKHR surface)
{
	Device::SwapChainSupportDetails details;
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
		requiredExtensions.erase(extension.extensionName);
	}
	return requiredExtensions.empty();
}

bool is_device_suitable(vk::PhysicalDevice const& device, vk::QueueFlagBits queue_flag,
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
}

void Device::pick_up_physical_device(vk::Instance instance, vk::QueueFlagBits queue_flag, std::vector<const char *> const &devicesExtension,
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

	utils::printFatalError("not suitable GPU found");
}

void Device::create_logical_device(std::vector<char const *> const &devicesExtension,
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

Device::Device(vk::Instance instance, vk::QueueFlagBits queue_flag, std::vector<const char *> const &devicesExtension,
			   VkSurfaceKHR surface, std::vector<const char *> const &validationLayers){
	pick_up_physical_device(instance, queue_flag, devicesExtension, surface);

	_swap_chain_details = query_swap_chain_support(_physical_device, surface);
	_indices = find_queue_families(_physical_device, surface, queue_flag);

	create_logical_device(devicesExtension, validationLayers);

}
