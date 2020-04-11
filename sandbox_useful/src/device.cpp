//
// Created by joe on 4/30/19.
//

#include <string_view>
#include "device.hpp"
#include <set>
#include "utils/utils.hpp"
#include "basicInit.hpp"
Device::QueueFamilyIndices find_queue_families(vk::PhysicalDevice const& device, VkSurfaceKHR surface, vk::QueueFlagBits queue_flag)
{
	Device::QueueFamilyIndices indices;
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
    _device.destroy(_command_pool);
    _device.destroy();
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

	utils::printFatalError("no suitable GPU found");
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

Device::Device(BasicInit const& context, vk::QueueFlagBits queue_flag, std::vector<const char *> const &devicesExtension, std::vector<const char *> const &validationLayers){
	auto const& surface = context.get_vk_surface();
	pick_up_physical_device(context.get_vk_instance(), queue_flag, devicesExtension,surface);

	_swap_chain_details = query_swap_chain_support(_physical_device, surface);
	_indices = find_queue_families(_physical_device, surface, queue_flag);

	create_logical_device(devicesExtension, validationLayers);
    create_command_pool();
}
void Device::create_command_pool(){
	vk::CommandPoolCreateInfo pool_info{
		{},
		static_cast<uint32_t>(_indices.graphics_family)
	};
	_command_pool = _device.createCommandPool(pool_info);
}

std::pair<vk::UniqueBuffer,
		vk::UniqueDeviceMemory> Device::create_buffer_and_memory(vk::DeviceSize const& size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags properties) const{
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
vk::UniqueDeviceMemory Device::create_device_memory(vk::MemoryRequirements const& mem_requirements, vk::MemoryPropertyFlags properties) const{
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

void Device::copy_buffer(vk::UniqueBuffer& destination, vk::UniqueBuffer const& source, vk::DeviceSize const& size) const{
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


















