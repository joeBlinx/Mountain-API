#include <iostream>
#include "sandbox_useful/initVulkan.hpp"
#include "sandbox_useful/context.hpp"
#include "sandbox_useful/swapChain.hpp"
#include "sandbox_useful/renderpass/renderPass.hpp"
#include <vector>
#include "sandbox_useful/buffer/vertex.hpp"
#include "glm/glm.hpp"
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
struct Model{
    glm::mat4 model {1};
};
struct Color{
    float new_color{};
};
struct Uniform{
   Model model;
   Color new_color{0.5};
};
struct object{
    buffer::vertex const& vertices;
    GraphicsPipeline const& graphics_pipeline;
    std::vector<Uniform> values;
};
struct move_rectangle{
    InitVulkan& init;
    PipelineData<Uniform> obj;
    void move(){
        //obj.values[0].model.dir += +0.2;
        init.createCommandBuffers(obj);
    }
};
void key_callback(GLFWwindow* window, int key, int , int action, int)
{
    auto* obj = static_cast<move_rectangle*>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_E && action == GLFW_PRESS){
        obj->move();
    }
    if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE){
        glfwSetWindowShouldClose(window, true);
    }
}
void loop(InitVulkan& init, Context const& context) {

    while (!glfwWindowShouldClose(context.get_window().get_window())) {
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
                 "Vulkan Window",
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
            Vertex{{-1.f, -1.f}, {1.0f, 0.0f, 0.0f}},
            Vertex{{1.f, -1.f}, {0.0f, 1.0f, 0.0f}},
            Vertex{{1.f, 1.f}, {0.0f, 0.0f, 1.0f}},
            Vertex{{-1.f, 1.f}, {1.0f, 1.0f, 1.0f}}
	};
	;
    std::vector<buffer::vertex> vertex_buffers;
    vertex_buffers.emplace_back(buffer::vertex(context,
           buffer::vertex_description(0, 0,
                       CLASS_DESCRIPTION(Vertex, position, color)),
                               vertices,
                               {0, 1, 2, 2, 3, 0}
            ));



	PushConstant<Model> push_vertex{
		vk::ShaderStageFlagBits::eVertex
	};
    PushConstant<Color> push_frag{
            vk::ShaderStageFlagBits::eFragment
    };
    GraphicsPipeline pipeline(context,
                              swap_chain,
                              render_pass,
                              vertex_buffers, push_vertex, push_frag);
	InitVulkan init(
            context,
            swap_chain,
            render_pass);

    move_rectangle move{init,
                        {vertex_buffers[0], pipeline,
                         {
                            {}}}};

    glfwSetKeyCallback(context.get_window().get_window(), key_callback);
    glfwSetWindowUserPointer(context.get_window().get_window(), &move);


    init.createCommandBuffers(move.obj);
	loop(init, context);

	return 0;
}