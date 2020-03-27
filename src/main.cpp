#include <iostream>
#include "../include/initVulkan.hpp"
#include "sandbox_useful/basicInit.hpp"
#include "sandbox_useful/device.hpp"
#include "sandbox_useful/swapChain.hpp"
#include "sandbox_useful/renderpass/renderPass.hpp"

int main() {
	const std::vector<const char*> validationLayers {
			"VK_LAYER_LUNARG_standard_validation"
	};
	std::vector<const char*> const devicesExtension{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	int constexpr width = 1366;
	int constexpr height = 768;

	BasicInit basic_init{width, height, "test"};


	Device device{ basic_init.get_vk_instance(),
				vk::QueueFlagBits::eGraphics,
				devicesExtension,
				basic_init.get_vk_surface(),
				validationLayers};


	SwapChain swap_chain{
			device.get_device(),
			basic_init.get_vk_surface(),
			device.get_queue_family_indice(),
			device.get_swap_chain_details(),
			vk::ImageUsageFlagBits::eColorAttachment,
			width,
			height
	};

	RenderPass render_pass = RenderPass::create<SubPass{subpass_attachment::COLOR}>(
			device.get_device(), swap_chain.get_swap_chain_image_format());

	InitVulkan init(
			basic_init.get_vk_instance(),
			basic_init.get_vk_surface(),
			device.get_device(),
			device.get_graphics_queue(),
			device.get_present_queue(),
			device.get_physical_device(),
			swap_chain.get_swap_chain(),
			swap_chain.get_swap_chain_image_views(),
			swap_chain.get_swap_chain_extent(),
			swap_chain.get_swap_chain_image_format(),
			device.get_queue_family_indice(),
			render_pass.get_renderpass());


	init.loop(basic_init.get_window());

	return 0;
}