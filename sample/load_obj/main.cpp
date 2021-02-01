#include <iostream>
#include "mountain/initVulkan.h"
#include "mountain/context.h"
#include "mountain/swapChain.h"
#include "mountain/renderpass/renderPass.h"
#include <vector>
#include <mountain/buffer/uniform.h>
#include <chrono>
#include <mountain/buffer/image2d.h>
#include <mountain/sampler.h>
#include "mountain/buffer/vertex.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "mountain/descriptor_setlayout_binding/descriptorset_layout.h"
#include "mountain/load_model.h"
#include "ressource_paths.h"

struct Model{
    glm::mat4 model {1};
};
struct Uniform{
   Model model;
};

struct move_rectangle{
    mountain::InitVulkan& init;
    mountain::PipelineData<Uniform> obj;
    void move(){
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
std::vector<mountain::buffer::vertex> create_buffers(mountain::Context const& context){

    auto [vertices_3d, indices_3d] = mountain::model::load_obj(std::filesystem::path(ASSETS_FOLDER /                                                                             "model/viking_room.obj"));
    std::vector<mountain::buffer::vertex> vertex_buffers;
    vertex_buffers.emplace_back(mountain::buffer::vertex(context,
                                                         mountain::buffer::vertex_description(0, 0,
                                                                                              mountain::model::Vertex::get_format_offset()),
                                                         vertices_3d,
                                                         std::move(indices_3d)
    ));
    return vertex_buffers;
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

    mountain::Context const context{width,
                 height,
                 "Mountain-API load obj sample",
                 devicesExtension};
    using mountain::subpass_attachment;
    mountain::RenderPass const render_pass{
        context,
        mountain::SubPass{subpass_attachment::COLOR, subpass_attachment::DEPTH}
    };

    mountain::SwapChain const swap_chain{
            context,
            render_pass,
            vk::ImageUsageFlagBits::eColorAttachment,
            width,
            height
    };


    auto const vertex_buffers = create_buffers(context);

    mountain::PushConstant<Model> const push_vertex{
		vk::ShaderStageFlagBits::eVertex
	};

    vk::DescriptorSetLayoutBinding const ubo_binding_layout =
            mountain::descriptorset_layout::create_descriptor_uniform(2, vk::ShaderStageFlagBits::eVertex);

    vk::DescriptorSetLayoutBinding const image_sampler_layout =
            mountain::descriptorset_layout::create_descriptor_image_sampler(1, vk::ShaderStageFlagBits::eFragment);

    vk::DescriptorSetLayout const descriptor_layout = mountain::descriptorset_layout::create_descriptorset_layout(
            context, {ubo_binding_layout, image_sampler_layout}
            );

    mountain::buffer::image2d const statue_image{context, ASSETS_FOLDER / "image/statue.jpg", 1};
    mountain::buffer::image2d const viking_image{context, ASSETS_FOLDER /"image/viking_room.png", 10};
    mountain::image::sampler const sampler(context, viking_image.get_mimap_levels());
    auto layouts = std::vector{descriptor_layout};
    mountain::GraphicsPipeline pipeline(context,
                              swap_chain,
                              render_pass,
                              std::array{
                                  mountain::shader{SHADER_FOLDER / "trianglevert.spv", vk::ShaderStageFlagBits::eVertex},
                                  mountain::shader{SHADER_FOLDER /"trianglefrag.spv", vk::ShaderStageFlagBits::eFragment}
                              },
                              vertex_buffers,
                              layouts,
                              push_vertex);
    mountain::InitVulkan init(
            context,
            swap_chain,
            render_pass, 2);
	init.allocate_descriptor_set(std::move(layouts));
    mountain::buffer::uniform<VP> uniform_vp(context, swap_chain.get_swap_chain_image_views().size());

    init.update_descriptor_set(0, 2, uniform_vp);

    init.update_descriptor_set(0, 1, viking_image, sampler);
    move_rectangle move{init,
                        {vertex_buffers[0], pipeline,
                         {{{}}}
                        }
    };

    glfwSetKeyCallback(context.get_window().get_window(), key_callback);

    glfwSetWindowUserPointer(context.get_window().get_window(), &move);

    init.createCommandBuffers(move.obj);

    std::vector<mountain::buffer::uniform_updater> updaters;
    updaters.emplace_back(uniform_vp.get_uniform_updater(create_vp_matrix(width, height)));
    while (!glfwWindowShouldClose(context.get_window().get_window())) {
        glfwPollEvents();
        init.drawFrame(std::move(updaters));
        move.rotate();
    }
    vkDeviceWaitIdle(context.get_device());

	return 0;
}
