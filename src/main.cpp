#include <iostream>
#include "sandbox_useful/initVulkan.hpp"
#include "sandbox_useful/basicInit.hpp"
#include "sandbox_useful/device.hpp"
#include "sandbox_useful/swapChain.hpp"
#include "sandbox_useful/renderpass/renderPass.hpp"
#include <vector>
#include "sandbox_useful/buffer/vertex.hpp"
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

	
	struct vec2{
		float a;
		float b;
	};
	struct vec3{
		float a, b, c;
	};
	struct Vertex{
		vec2 position;
		vec3 color;
	};
	std::array vertices{
            Vertex{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            Vertex{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            Vertex{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
            Vertex{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
	};
	;
    std::vector<buffer::vertex> vertex;
    vertex.emplace_back(buffer::vertex(device,
            buffer::vertex_description(0, 0, CLASS_DESCRIPTION(Vertex, position, color)),
            vertices,
            {0, 1, 2, 2, 3, 0}
            ));

    GraphicsPipeline pipeline(device,
                              swap_chain,
                              render_pass,
                              {vertex});
	InitVulkan init(
            context,
            device,
            swap_chain,
            render_pass,
            pipeline,
            {vertex});

	init.loop(context.get_window());

	return 0;
}