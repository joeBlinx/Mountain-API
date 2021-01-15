#include <iostream>
#include "sandbox_useful/initVulkan.hpp"
#include "sandbox_useful/context.hpp"
#include "sandbox_useful/swapChain.hpp"
#include "sandbox_useful/renderpass/renderPass.hpp"
#include <vector>
#include <sandbox_useful/buffer/uniform.h>
#include <chrono>
#include <sandbox_useful/buffer/image2d.h>
#include <sandbox_useful/sampler.h>
#include "sandbox_useful/buffer/vertex.hpp"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "sandbox_useful/descriptor_setlayout_binding/descriptorset_layout.h"
#include "sandbox_useful/load_model.h"
struct vec2{
    float a;
    float b;
};
struct vec3{
    float a, b, c;
};
struct Vertex{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 tex_coord;
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

struct move_rectangle{
    InitVulkan& init;
    PipelineData<Uniform> obj;
    void move(){
        //obj.values[0].model.dir += +0.2;
        init.createCommandBuffers(obj);
    }
    void rotate(){
        static auto startTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
        obj.push_constant_values[0].model.model = glm::rotate(glm::mat4{1.}, time*glm::radians<float>(30.), glm::vec3(0., 0., 1.));
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

    RenderPass render_pass{
        context,
        SubPass{subpass_attachment::COLOR, subpass_attachment::DEPTH}
    };

    SwapChain swap_chain{
            context,
            render_pass,
            vk::ImageUsageFlagBits::eColorAttachment,
            width,
            height
    };


    auto [vertices_3d, indices_3d] = model::load_obj(std::filesystem::path("assets/model/viking_room.obj"));
    std::vector<buffer::vertex> vertex_buffers;
    vertex_buffers.emplace_back(buffer::vertex(context,
           buffer::vertex_description(0, 0,
                       model::Vertex::get_format_offset()),
                               vertices_3d,
                               std::move(indices_3d)
            ));


	PushConstant<Model> push_vertex{
		vk::ShaderStageFlagBits::eVertex
	};
    PushConstant<Color> push_frag{
            vk::ShaderStageFlagBits::eFragment
    };

    vk::DescriptorSetLayoutBinding ubo_binding_layout =
            descriptorset_layout::create_descriptor_uniform(2, vk::ShaderStageFlagBits::eVertex);

    vk::DescriptorSetLayoutBinding image_sampler_layout =
            descriptorset_layout::create_descriptor_image_sampler(1, vk::ShaderStageFlagBits::eFragment);

    vk::DescriptorSetLayoutBinding ubo_layout_frag_color =
            descriptorset_layout::create_descriptor_uniform(0, vk::ShaderStageFlagBits::eFragment);

    vk::DescriptorSetLayout descriptor_layout = descriptorset_layout::create_descriptorset_layout(
            context, {ubo_binding_layout, image_sampler_layout}
            );
    vk::DescriptorSetLayout descriptor_layout_frag = descriptorset_layout::create_descriptorset_layout(
            context, {ubo_layout_frag_color}
    );

    buffer::image2d statue_image{context, "assets/image/statue.jpg", 1};
    buffer::image2d viking_image{context, "assets/image/viking_room.png", 10};
    image::sampler sampler(context, viking_image.get_mimap_levels());
    auto layouts = std::vector{descriptor_layout, descriptor_layout_frag};
    GraphicsPipeline pipeline(context,
                              swap_chain,
                              render_pass,
                              std::array{
                                  shader{"trianglevert.spv", vk::ShaderStageFlagBits::eVertex},
                                  shader{"trianglefrag.spv", vk::ShaderStageFlagBits::eFragment}
                              },
                              vertex_buffers,
                              layouts,
                              push_vertex, push_frag);
	InitVulkan init(
            context,
            swap_chain,
            render_pass, 2);
	init.allocate_descriptor_set(std::move(layouts));
	buffer::uniform<VP> uniform_vp(context, swap_chain.get_swap_chain_image_views().size());
    buffer::uniform<float> uniform_color(context, swap_chain.get_swap_chain_image_views().size());
    init.update_descriptor_set(0, 2, uniform_vp);
    init.update_descriptor_set(1, 0, uniform_color);
    init.update_descriptor_set(0, 1, viking_image, sampler);
    move_rectangle move{init,
                        {vertex_buffers[0], pipeline,
                         {
                            {
                {}}
                         }
                        }
    };

    glfwSetKeyCallback(context.get_window().get_window(), key_callback);


    glfwSetWindowUserPointer(context.get_window().get_window(), &move);


    init.createCommandBuffers(move.obj);

    std::vector<buffer::uniform_updater> updaters;
    updaters.emplace_back(uniform_color.get_uniform_updater(2.0f));
    updaters.emplace_back(uniform_vp.get_uniform_updater(create_vp_matrix(width, height)));
    while (!glfwWindowShouldClose(context.get_window().get_window())) {
        glfwPollEvents();
        init.drawFrame(std::move(updaters));
        move.rotate();
    }
    vkDeviceWaitIdle(context.get_device());

	return 0;
}
