//
// Created by joe on 5/1/19.
//

#ifndef SANDBOX_SWAPCHAIN_HPP
#define SANDBOX_SWAPCHAIN_HPP

#include <vulkan/vulkan.hpp>
#include <vector>
#include "sandbox_useful/context.hpp"
#include "swapChain.hpp"
struct RenderPass;
struct Context;
struct SwapChain {

	SwapChain(Context const &context, RenderPass const &render_pass, vk::ImageUsageFlags image_usage, int width,
              int height);
	SwapChain(SwapChain const&) = delete;
    SwapChain& operator=(SwapChain const&) = delete;
	~SwapChain();

	vk::SwapchainKHR get_swap_chain() const;

	const std::vector<vk::UniqueImageView> & get_swap_chain_image_views()
	const;

	std::vector<vk::Framebuffer> get_framebuffers() const;
	vk::Format get_swap_chain_image_format() const;

	const vk::Extent2D &get_swap_chain_extent() const;

private:
	Context const& _context;
	vk::SwapchainKHR _swap_chain;
    vk::UniqueImageView _depth_image_view;
    vk::UniqueDeviceMemory _depth_image_memory;
    vk::UniqueImage _depth_image;
    std::vector<vk::UniqueFramebuffer> _swapchain_frame_buffers;
    std::vector<vk::UniqueImageView> _swap_chain_image_views;
    std::vector<vk::Image> _swap_chain_images;

	vk::Format _swap_chain_image_format{};
	vk::Extent2D _swap_chain_extent{};

	void create_depth_resources();
	void create_swap_chain(Context const &context, vk::ImageUsageFlags image_usage, int width, int height); // there are some parameter
	void create_image_views();
	void create_frame_buffer(const RenderPass &render_pass);
};



#endif //SANDBOX_SWAPCHAIN_HPP
