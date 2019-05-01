//
// Created by joe on 5/1/19.
//


#include <log.hpp>
#include "swapChain.hpp"
#include "device.hpp"

VkSurfaceFormatKHR chooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR> const & available_formats)
{
	if (available_formats.size() == 1 && available_formats[0].format == VK_FORMAT_UNDEFINED) {
		return { VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
	}

	for (const auto& availableFormat : available_formats) {
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat;
		}
	}

	return available_formats[0];
}

VkPresentModeKHR chooseSwapPresentMode(std::vector<VkPresentModeKHR> const & available_present_modes)
{
	VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

	for (const auto& availablePresentMode : available_present_modes) {
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return availablePresentMode;
		}
		else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
			bestMode = availablePresentMode;
		}
	}

	return bestMode;
}
VkExtent2D chooseSwapExtent(VkSurfaceCapabilitiesKHR const &capabilities, int width, int height)
{
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		return capabilities.currentExtent;
	}
	else {
		VkExtent2D actualExtent{ (uint32_t)width, (uint32_t)height };

		actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
		actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

		return actualExtent;
	}
}
void SwapChain::create_swap_chain(VkSurfaceKHR surface, Device::QueueFamilyIndices const &indices,
								  Device::SwapChainSupportDetails const &swap_chain_support,
								  VkImageUsageFlags image_usage, int width, int height) {


	VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swap_chain_support.formats);
	VkPresentModeKHR presentMode = chooseSwapPresentMode(swap_chain_support.presentModes);
	_swap_chain_extent = chooseSwapExtent(swap_chain_support.capabilities, width, height);


	uint32_t imageCount = swap_chain_support.capabilities.minImageCount + 1;
	if (swap_chain_support.capabilities.maxImageCount > 0 && imageCount > swap_chain_support.capabilities.maxImageCount) {
		imageCount = swap_chain_support.capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = surface;
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = _swap_chain_extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = image_usage; // can change


	uint32_t queueFamilyIndices[] = { static_cast<uint32_t>(indices.graphics_family),
									  static_cast<uint32_t>(indices.present_family) };

	if (indices.graphics_family != indices.present_family) {
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT; // one queue for all
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else {
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; // one queue for each mode, graphics, present
		createInfo.queueFamilyIndexCount = 0; // Optional
		createInfo.pQueueFamilyIndices = nullptr; // Optional
	}
	createInfo.preTransform = swap_chain_support.capabilities.currentTransform; // specify transform apply to swap chain
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; // alpha with other window
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE; // don't care about color pixel in other window
	createInfo.oldSwapchain = VK_NULL_HANDLE; // no old swap chain..for now

	checkError(vkCreateSwapchainKHR(_device, &createInfo, nullptr, &_swap_chain),
			   "unable to create swapchain");

	vkGetSwapchainImagesKHR(_device, _swap_chain, &imageCount, nullptr); //get the number of image the swapchain can handle
	_swap_chain_images.resize(imageCount);
	vkGetSwapchainImagesKHR(_device, _swap_chain, &imageCount, _swap_chain_images.data());

	_swap_chain_image_format = surfaceFormat.format;

}

void SwapChain::create_image_views() {

	_swap_chain_image_views.resize(_swap_chain_images.size());
	for (size_t i = 0; i < _swap_chain_image_views.size(); i++)
	{
		VkImageViewCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = _swap_chain_images[i];
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = _swap_chain_image_format;
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
				vkCreateImageView(_device, &createInfo, nullptr, &_swap_chain_image_views[i]),
				"unable to create Image View"
		);
	}
}

SwapChain::~SwapChain() {

	for (auto& imageView : _swap_chain_image_views) {
		vkDestroyImageView(_device, imageView, nullptr);
	}
	vkDestroySwapchainKHR(_device, _swap_chain, nullptr);
}

SwapChain::SwapChain(VkDevice device, VkSurfaceKHR surface, Device::QueueFamilyIndices const &indices,
					 Device::SwapChainSupportDetails const &swap_chain_support, VkImageUsageFlags image_usage,
					 int width, int height) : _device(device) {
	create_swap_chain(surface, indices, swap_chain_support, image_usage, width, height);
	create_image_views();

}

VkSwapchainKHR SwapChain::get_swap_chain() const {
	return _swap_chain;
}

const std::vector<VkImageView> &SwapChain::get_swap_chain_image_views() const {
	return _swap_chain_image_views;
}

VkFormat SwapChain::get_swap_chain_image_format() const {
	return _swap_chain_image_format;
}

const VkExtent2D &SwapChain::get_swap_chain_extent() const {
	return _swap_chain_extent;
}
