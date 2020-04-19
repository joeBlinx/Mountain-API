#include <iostream>
#include "sandbox_useful/initVulkan.hpp"
#include "sandbox_useful/context.hpp"
#include "sandbox_useful/swapChain.hpp"
#include "sandbox_useful/renderpass/renderPass.hpp"
#include <vector>
#include "sandbox_useful/buffer/vertex.hpp"
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

int main() {
	
	std::vector<const char*> const devicesExtension{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	int constexpr width = 1366;
	int constexpr height = 768;

	Context context{width,
                 height,
                 "test",
                 devicesExtension};

	SwapChain swap_chain{
            context,
            vk::ImageUsageFlagBits::eColorAttachment,
            width,
            height
    };

	RenderPass render_pass = RenderPass::create<SubPass{subpass_attachment::COLOR}>(
			context.get_device(), swap_chain.get_swap_chain_image_format());


	std::array vertices{
            Vertex{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            Vertex{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            Vertex{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
            Vertex{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
	};
	;
    std::vector<buffer::vertex> vertex;
    vertex.emplace_back(buffer::vertex(context,
            buffer::vertex_description(0, 0, CLASS_DESCRIPTION(Vertex, position, color)),
            vertices,
            {0, 1, 2, 2, 3, 0}
            ));

    GraphicsPipeline pipeline(context,
                              swap_chain,
                              render_pass,
                              {vertex});
	InitVulkan init(
            context,
            swap_chain,
            render_pass,
            pipeline,
            {vertex});

	init.loop(context.get_window());

	return 0;
}