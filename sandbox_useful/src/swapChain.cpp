//
// Created by joe on 5/1/19.
//


#include "swapChain.hpp"
#include "utils/log.hpp"
#include "device.hpp"
#include  <algorithm>
vk::SurfaceFormatKHR chooseSwapSurfaceFormat(std::vector<vk::SurfaceFormatKHR> const & available_formats)
{
	if (available_formats.size() == 1 && available_formats[0].format == vk::Format::eUndefined) {
		return { vk::Format::eB8G8R8A8Unorm, vk::ColorSpaceKHR::eSrgbNonlinear };
	}

	for (const auto& availableFormat : available_formats) {
		if (availableFormat.format == vk::Format::eB8G8R8A8Unorm && availableFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
			return availableFormat;
		}
	}

	return available_formats[0];
}

vk::PresentModeKHR chooseSwapPresentMode(std::vector<vk::PresentModeKHR> const & available_present_modes)
{
	vk::PresentModeKHR bestMode = vk::PresentModeKHR::eFifo;

	for (const auto& availablePresentMode : available_present_modes) {
		if (availablePresentMode == vk::PresentModeKHR::eMailbox) {
			return availablePresentMode;
		}
		else if (availablePresentMode == vk::PresentModeKHR::eImmediate) {
			bestMode = availablePresentMode;
		}
	}

	return bestMode;
}
vk::Extent2D chooseSwapExtent(VkSurfaceCapabilitiesKHR const &capabilities, int width, int height)
{
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		return capabilities.currentExtent;
	}
	else {
		vk::Extent2D actualExtent{ (uint32_t)width, (uint32_t)height };

		actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
		actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

		return actualExtent;
	}
}
void SwapChain::create_swap_chain(VkSurfaceKHR surface, Device::QueueFamilyIndices const &indices,
                                  Device::SwapChainSupportDetails const &swap_chain_support,
                                  vk::ImageUsageFlags image_usage, int width, int height) {


	vk::SurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swap_chain_support.formats);
	vk::PresentModeKHR presentMode = chooseSwapPresentMode(swap_chain_support.presentModes);
	_swap_chain_extent = chooseSwapExtent(swap_chain_support.capabilities, width, height);


	uint32_t imageCount = swap_chain_support.capabilities.minImageCount + 1;
	if (swap_chain_support.capabilities.maxImageCount > 0 && imageCount > swap_chain_support.capabilities.maxImageCount) {
		imageCount = swap_chain_support.capabilities.maxImageCount;
	}

	vk::SwapchainCreateInfoKHR createInfo = {};
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
		createInfo.imageSharingMode = vk::SharingMode::eConcurrent; // one queue for all
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else {
		createInfo.imageSharingMode = vk::SharingMode::eExclusive; // one queue for each mode, graphics, present
		createInfo.queueFamilyIndexCount = 0; // Optional
		createInfo.pQueueFamilyIndices = nullptr; // Optional
	}
	createInfo.preTransform = swap_chain_support.capabilities.currentTransform; // specify transform apply to swap chain
	createInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque; // alpha with other window
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE; // don't care about color pixel in other window
	//createInfo.oldSwapchain ; // no old swap chain..for now
    _swap_chain = _device.createSwapchainKHR(createInfo);

	_swap_chain_images = _device.getSwapchainImagesKHR(_swap_chain);
	_swap_chain_image_format = surfaceFormat.format;

}

void SwapChain::create_image_views() {

	_swap_chain_image_views.resize(_swap_chain_images.size());
	for (size_t i = 0; i < _swap_chain_image_views.size(); i++)
	{
		vk::ImageViewCreateInfo createInfo;
		createInfo.image = _swap_chain_images[i];
		createInfo.viewType = vk::ImageViewType::e2D;
		createInfo.format = _swap_chain_image_format;
		createInfo.components.r = vk::ComponentSwizzle::eIdentity;
		createInfo.components.g = vk::ComponentSwizzle::eIdentity;
		createInfo.components.b = vk::ComponentSwizzle::eIdentity;
		createInfo.components.a = vk::ComponentSwizzle::eIdentity;
		createInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;
		_swap_chain_image_views[i] = _device.createImageView(createInfo);
	}
}

SwapChain::~SwapChain() {

	for (auto& imageView : _swap_chain_image_views) {
		vkDestroyImageView(_device, imageView, nullptr);
	}
	vkDestroySwapchainKHR(_device, _swap_chain, nullptr);
}

SwapChain::SwapChain(vk::Device device, VkSurfaceKHR surface, Device::QueueFamilyIndices const &indices,
                     Device::SwapChainSupportDetails const &swap_chain_support, vk::ImageUsageFlags image_usage,
                     int width, int height) : _device(device) {
	create_swap_chain(surface, indices, swap_chain_support, image_usage, width, height);
	create_image_views();

}

vk::SwapchainKHR SwapChain::get_swap_chain() const {
	return _swap_chain;
}

const std::vector<vk::ImageView> &SwapChain::get_swap_chain_image_views() const {
	return _swap_chain_image_views;
}

vk::Format SwapChain::get_swap_chain_image_format() const {
	return _swap_chain_image_format;
}

const vk::Extent2D &SwapChain::get_swap_chain_extent() const {
	return _swap_chain_extent;
}
