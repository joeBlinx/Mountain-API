#include <iostream>
#include "sandbox_useful/initVulkan.hpp"
#include "sandbox_useful/context.hpp"
#include "sandbox_useful/swapChain.hpp"
#include "sandbox_useful/renderpass/renderPass.hpp"
#include <vector>
#include <sandbox_useful/buffer/uniform.h>
#include <chrono>
#include "sandbox_useful/buffer/vertex.hpp"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
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
struct VP{
    glm::mat4 view{1.};
    glm::mat4 proj{1.};
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
VP create_vp_matrix(int width, int height){
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
    (void)time;
    VP ubo{};
    ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.proj = glm::perspective(glm::radians(45.0f),
                                width / (float) height,
                                0.1f, 10.0f);
    ubo.proj[1][1] *= -1;

    return ubo;
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
            Vertex{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            Vertex{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            Vertex{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
            Vertex{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
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

    vk::DescriptorSetLayoutBinding ubo_binding_layout{};
    ubo_binding_layout.binding = 0;
    ubo_binding_layout.descriptorType = vk::DescriptorType::eUniformBuffer;
    ubo_binding_layout.descriptorCount = 1;
    ubo_binding_layout.stageFlags = vk::ShaderStageFlagBits::eVertex;


    vk::DescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{};
    descriptorSetLayoutCreateInfo.bindingCount = 1;
    descriptorSetLayoutCreateInfo.pBindings = &ubo_binding_layout;

    vk::DescriptorSetLayout descriptor_layout;
    context.get_device().createDescriptorSetLayout(&descriptorSetLayoutCreateInfo,
                                                                            nullptr,
                                                                            &descriptor_layout);
    GraphicsPipeline pipeline(context,
                              swap_chain,
                              render_pass,
                              vertex_buffers,
                              {descriptor_layout},
                              push_vertex, push_frag);
	InitVulkan init(
            context,
            swap_chain,
            render_pass);
	buffer::uniform<VP> uniform_vp(context, swap_chain.get_swap_chain_image_views().size());
    init.create_descriptor_sets_uniforms({descriptor_layout},
                                         uniform_vp);
    move_rectangle move{init,
                        {vertex_buffers[0], pipeline,
                         {
                            {
                {glm::scale(glm::mat4{1.}, glm::vec3{1.})}}

                         }
                        }
    };

    glfwSetKeyCallback(context.get_window().get_window(), key_callback);
    glfwSetWindowUserPointer(context.get_window().get_window(), &move);


    init.createCommandBuffers(move.obj);

    std::vector<buffer::uniform_updater> updaters;
    updaters.emplace_back(uniform_vp.get_uniform_updater(create_vp_matrix(width, height)));
    while (!glfwWindowShouldClose(context.get_window().get_window())) {
        glfwPollEvents();
        init.drawFrame(std::move(updaters));
    }
    vkDeviceWaitIdle(context.get_device());

	return 0;
}
