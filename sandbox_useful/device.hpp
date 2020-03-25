//
// Created by joe on 4/30/19.
//

#ifndef SANDBOX_DEVICE_HPP
#define SANDBOX_DEVICE_HPP

#include <vulkan/vulkan.hpp>
#include <vector>

struct Device {

	Device(vk::Instance instance, vk::QueueFlagBits queue_flag, std::vector<const char *> const &devicesExtension,
		   VkSurfaceKHR surface, std::vector<const char *> const &validationLayers);
	~Device();
	struct QueueFamilyIndices{
		static int constexpr number_queue = 1;
		int graphics_family = -1;
		int present_family = -1;

		bool isComplete(){
			return graphics_family >=0  && present_family >= 0;
		}
	};
	struct SwapChainSupportDetails
	{
		vk::SurfaceCapabilitiesKHR capabilities;
		std::vector<vk::SurfaceFormatKHR> formats;
		std::vector <vk::PresentModeKHR> presentModes;
	};

	vk::Device get_device() { return _device; }
	VkQueue get_graphics_queue() {return _graphics_queue;}
	VkQueue get_present_queue() {return _present_queue;}
	VkPhysicalDevice get_physical_device() { return _physical_device;}
	QueueFamilyIndices const& get_queue_family_indice() { return _indices; }
	SwapChainSupportDetails const& get_swap_chain_details() { return _swap_chain_details; }
private:

	vk::PhysicalDevice _physical_device;
	vk::Device _device;

	VkQueue  _graphics_queue = nullptr;
	VkQueue  _present_queue = nullptr;

	QueueFamilyIndices _indices;

	SwapChainSupportDetails _swap_chain_details;

	void pick_up_physical_device(vk::Instance instance, vk::QueueFlagBits queue_flag, std::vector<const char *> const &devicesExtension,
								 VkSurfaceKHR surface);
	void create_logical_device(std::vector<char const *> const &devicesExtension,
							   std::vector<const char *> const &validationLayers);

};


#endif //SANDBOX_DEVICE_HPP
