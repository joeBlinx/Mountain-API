//
// Created by joe on 5/1/19.
//

#ifndef SANDBOX_SWAPCHAIN_HPP
#define SANDBOX_SWAPCHAIN_HPP

#include <vulkan/vulkan.h>
#include <vector>
#include "device.hpp"

struct SwapChain {

	SwapChain(VkDevice device, VkSurfaceKHR surface, Device::QueueFamilyIndices const &indices,
			  Device::SwapChainSupportDetails const &swap_chain_support, VkImageUsageFlags image_usage,
			  int width, int height);
	~SwapChain();

	VkSwapchainKHR get_swap_chain() const;

	const std::vector<VkImageView> &get_swap_chain_image_views() const;

	VkFormat get_swap_chain_image_format() const;

	const VkExtent2D &get_swap_chain_extent() const;

private:
	VkDevice _device = nullptr;
	VkSwapchainKHR _swap_chain = nullptr;
	std::vector<VkImage> _swap_chain_images;
	std::vector<VkImageView> _swap_chain_image_views;
	VkFormat _swap_chain_image_format{};


	VkExtent2D _swap_chain_extent{};

	void create_swap_chain(VkSurfaceKHR surface, Device::QueueFamilyIndices const &indices,
						   Device::SwapChainSupportDetails const &swap_chain_support,
						   VkImageUsageFlags image_usage, int width, int height); // there are some parameter
	void create_image_views();
};


#endif //SANDBOX_SWAPCHAIN_HPP
