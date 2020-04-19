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
struct Test{
    float dir{};
    float size{};
    float new_color{0.5};
};
struct object{
    buffer::vertex const& vertices;
    std::vector<Test> values;
};
struct move_rectangle{
    InitVulkan& init;
    object obj;
    void move(){
        obj.values[0].dir += +0.2;
        init.createCommandBuffers(obj);
    }
};
void key_callback(GLFWwindow* window, int key, int , int action, int)
{
    auto* obj = static_cast<move_rectangle*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_E && action == GLFW_PRESS){
        obj->move();

    }
}
void loop(InitVulkan& init, Context const& context) {

    while (!glfwWindowShouldClose(context.get_window())) {
        glfwPollEvents();
        init.drawFrame();
    }
    vkDeviceWaitIdle(context.get_device());
}

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
    glfwSetKeyCallback(context.get_window(), key_callback);
	SwapChain swap_chain{
            context,
            vk::ImageUsageFlagBits::eColorAttachment,
            width,
            height
    };

	RenderPass render_pass = RenderPass::create<SubPass{subpass_attachment::COLOR}>(
			context.get_device(), swap_chain.get_swap_chain_image_format());


	std::array vertices{
            Vertex{{-1.f, -1.f}, {1.0f, 0.0f, 0.0f}},
            Vertex{{1.f, -1.f}, {0.0f, 1.0f, 0.0f}},
            Vertex{{1.f, 1.f}, {0.0f, 0.0f, 1.0f}},
            Vertex{{-1.f, 1.f}, {1.0f, 1.0f, 1.0f}}
	};
	;
    std::vector<buffer::vertex> vertex;
    vertex.emplace_back(buffer::vertex(context,
            buffer::vertex_description(0, 0, CLASS_DESCRIPTION(Vertex, position, color)),
            vertices,
            {0, 1, 2, 2, 3, 0}
            ));

	struct Vertex{
        float dir{};
        float size{};
	};
	struct Fragment{
	    float new_color{};
	};

	PushConstant<Vertex> push_vertex{
		vk::ShaderStageFlagBits::eVertex
	};
    PushConstant<Fragment> push_frag{
            vk::ShaderStageFlagBits::eFragment
    };
    GraphicsPipeline pipeline(context,
                              swap_chain,
                              render_pass,
                              vertex, push_vertex, push_frag);
	InitVulkan init(
            context,
            swap_chain,
            render_pass,
            pipeline);

    move_rectangle move{init, {vertex[0], {{0.5, 0.25}, {-1, 0.25}, {0, 0.25}}}};
    glfwSetWindowUserPointer(context.get_window(), &move);
    init.createCommandBuffers(move.obj);
	loop(init, context);

	return 0;
}