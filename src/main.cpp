#include <iostream>
#include "sandbox_useful/initVulkan.hpp"
#include "sandbox_useful/basicInit.hpp"
#include "sandbox_useful/device.hpp"
#include "sandbox_useful/swapChain.hpp"
#include "sandbox_useful/renderpass/renderPass.hpp"
#include <vector>
#include "sandbox_useful/buffer/array_buffer.hpp"
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
            device,
            context,
            vk::ImageUsageFlagBits::eColorAttachment,
            width,
            height
	};

	RenderPass render_pass = RenderPass::create<SubPass{subpass_attachment::COLOR}>(
			device.get_device(), swap_chain.get_swap_chain_image_format());

	

	struct Test{
		float position[2];
		float color[3];
	};
	buffer::array::vertex_description vertex_description(0, 0, CLASS_DESCRIPTION(Test, position, color));
	InitVulkan init = InitVulkan::create_vulkan(
            context,
            device,
            swap_chain,
            render_pass, vertex_description);
	init.loop(context.get_window());

	return 0;
}