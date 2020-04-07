#include <iostream>
#include "sandbox_useful/initVulkan.hpp"
#include "sandbox_useful/basicInit.hpp"
#include "sandbox_useful/device.hpp"
#include "sandbox_useful/swapChain.hpp"
#include "sandbox_useful/renderpass/renderPass.hpp"
#include <vector>

int main() {
	const std::vector<const char*> validationLayers {
			"VK_LAYER_LUNARG_standard_validation"
	};
	std::vector<const char*> const devicesExtension{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	int constexpr width = 1366;
	int constexpr height = 768;

	BasicInit context{width, height, "test"};


	Device device{context,
                  vk::QueueFlagBits::eGraphics,
                  devicesExtension,
                  validationLayers};


	SwapChain swap_chain{
            device.get_device(),
            context.get_vk_surface(),
            device.get_queue_family_indice(),
            device.get_swap_chain_details(),
            vk::ImageUsageFlagBits::eColorAttachment,
            width,
            height
	};

	RenderPass render_pass = RenderPass::create<SubPass{subpass_attachment::COLOR}>(
			device.get_device(), swap_chain.get_swap_chain_image_format());

	InitVulkan init(
            context,
            device,
            swap_chain,
            device.get_queue_family_indice(),
            render_pass.get_renderpass());


	init.loop(context.get_window());

	return 0;
}