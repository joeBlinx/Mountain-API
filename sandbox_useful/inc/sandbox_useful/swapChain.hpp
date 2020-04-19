//
// Created by joe on 5/1/19.
//

#ifndef SANDBOX_SWAPCHAIN_HPP
#define SANDBOX_SWAPCHAIN_HPP

#include <vulkan/vulkan.hpp>
#include <vector>
#include "sandbox_useful/context.hpp"

class Context;
struct SwapChain {

	SwapChain(Context const &context, vk::ImageUsageFlags image_usage, int width, int height);
	SwapChain(SwapChain const&) = delete;
    SwapChain& operator=(SwapChain const&) = delete;
	~SwapChain();

	vk::SwapchainKHR get_swap_chain() const;

	const std::vector<vk::ImageView> &get_swap_chain_image_views() const;

	vk::Format get_swap_chain_image_format() const;

	const vk::Extent2D &get_swap_chain_extent() const;

private:
	vk::Device const& _device;
	vk::SwapchainKHR _swap_chain;
	std::vector<vk::Image> _swap_chain_images;
	std::vector<vk::ImageView> _swap_chain_image_views;
	vk::Format _swap_chain_image_format{};


	vk::Extent2D _swap_chain_extent{};

	void create_swap_chain(VkSurfaceKHR surface, const Context::QueueFamilyIndices &indices,
                           const Context::SwapChainSupportDetails &swap_chain_support,
                           vk::ImageUsageFlags image_usage, int width, int height); // there are some parameter
	void create_image_views();
};


#endif //SANDBOX_SWAPCHAIN_HPP
