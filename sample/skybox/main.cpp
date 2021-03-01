#include <iostream>
#include "mountain/command_buffer.h"
#include "mountain/context.h"
#include "mountain/swapChain.h"
#include "mountain/render_pass.h"
#include <vector>
#include "mountain/uniform.h"
#include <chrono>
#include <mountain/pipeline_builder.h>
#include "mountain/image2d.h"
#include "mountain/sampler.h"
#include "mountain/vertex.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "mountain/descriptorset_layout.h"
#include "mountain/load_model.h"
#include "ressource_paths.h"
#include "GLFW/glfw3.h"
#include "mountain/subpass.h"
#include <span>
struct Model{
    glm::mat4 model;
};
Model rotate(){
    static auto startTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
    return Model(glm::rotate(glm::mat4{1.}, time*glm::radians<float>(30.), glm::vec3(0., 0., 1.)));
}
struct VP{
    glm::mat4 view{1.};
    glm::mat4 proj{1.};
};
void key_callback(GLFWwindow* window, int key, int , int action, int)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE){
        glfwSetWindowShouldClose(window, true);
    }
}
std::vector<mountain::buffer::vertex> create_buffers(mountain::Context const& context){

    auto [vertices_3d, indices_3d] = mountain::model::load_obj(std::filesystem::path(ASSETS_FOLDER /                                                                             "model/viking_room.obj"));
    std::vector<mountain::buffer::vertex> vertex_buffers;
    vertex_buffers.emplace_back(mountain::buffer::vertex(context,
                                                         mountain::buffer::vertex_description(0, 0,
                                                                                              mountain::model::Vertex::get_format_offsets()),
                                                         vertices_3d,
                                                         std::move(indices_3d)
    ));
    return vertex_buffers;
}
VP create_vp_matrix(int width, int height){


    VP ubo{};
    ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.proj = glm::perspective(glm::radians(45.0f),
                                (float) width / (float) height,
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
    mountain::Window const window{"Mountain-API load obj sample\"", width, height};
    mountain::Context const context{window,
                                    devicesExtension};


    mountain::RenderPass const render_pass{
            context,
            {mountain::RenderPass::COLOR | mountain::RenderPass::DEPTH,
             mountain::RenderPass::COLOR},
            {[] {
                vk::SubpassDependency dependency = {};
                dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
                dependency.srcAccessMask = static_cast<vk::AccessFlagBits>(0);
                dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput|
                                          vk::PipelineStageFlagBits::eEarlyFragmentTests;
                dependency.dstAccessMask =
                        vk::AccessFlagBits::eColorAttachmentWrite
                        |vk::AccessFlagBits::eDepthStencilAttachmentWrite;
                return dependency;
            }(),
             [] {
                 vk::SubpassDependency dependency = {};
                 dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
                 dependency.srcAccessMask = static_cast<vk::AccessFlagBits>(0);
                 dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput|
                                           vk::PipelineStageFlagBits::eEarlyFragmentTests;
                 dependency.dstAccessMask =
                         vk::AccessFlagBits::eColorAttachmentWrite
                         |vk::AccessFlagBits::eDepthStencilAttachmentWrite;
                 return dependency;
             }()
            }
    };

    mountain::SwapChain const swap_chain{
            context,
            render_pass,
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

    // DEPTH AND STENCIL
    vk::PipelineDepthStencilStateCreateInfo depth_stencil;
    depth_stencil.depthTestEnable = VK_TRUE;
    depth_stencil.depthWriteEnable = VK_TRUE;
    depth_stencil.depthCompareOp = vk::CompareOp::eLess;
    depth_stencil.stencilTestEnable = VK_FALSE;
    auto const shaders = std::array{
            mountain::shader{SHADER_FOLDER / "vikingvert.spv", vk::ShaderStageFlagBits::eVertex},
            mountain::shader{SHADER_FOLDER / "vikingfrag.spv", vk::ShaderStageFlagBits::eFragment}
    };
    mountain::GraphicsPipeline pipeline = mountain::PipelineBuilder(context)
            .create_assembly(vk::PrimitiveTopology::eTriangleList)
            .create_viewport_info(swap_chain.get_swap_chain_extent())
            .create_depth_stencil_state(depth_stencil)
            .create_shaders_info(shaders)
            .create_vertex_info(vertex_buffers)
            .create_rasterizer(vk::PolygonMode::eFill)
            .create_mutlisampling()
            .define_subpass(mountain::SubPass{&render_pass, 0})
            .create_color_blend_state()
            .create_pipeline_layout(layouts, push_vertex)
            .build();

    mountain::CommandBuffer init(
            context,
            swap_chain,
            render_pass, 2);
    init.allocate_descriptor_set(std::move(layouts));
    mountain::buffer::uniform<VP> uniform_vp(context, swap_chain.get_swap_chain_image_views().size());

    init.update_descriptor_set(0, 2, uniform_vp);

    init.update_descriptor_set(0, 1, viking_image, sampler);

    glfwSetKeyCallback(context.get_window().get_window(), key_callback);

    auto record = [&](Model const& rotation) {
        init.record([&](mountain::CommandBuffer const &command_api, std::size_t const index) {
            auto const &command = command_api.get_command_buffer(index);
            command.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline.get_pipeline());
            std::array size = {vk::DeviceSize(0)};
            auto const &vertex = vertex_buffers[0];
            command.bindVertexBuffers(0, 1, &vertex.get_buffer(), size.data());
            command.bindIndexBuffer(vertex.get_buffer(), vertex.get_indices_offset(), vk::IndexType::eUint32);
            auto const[descriptor_set, size_descriptor_set] = command_api.get_descriptor_set_size(index);
            command.bindDescriptorSets(vk::PipelineBindPoint::eGraphics,
                                       pipeline.get_pipeline_layout(),
                                       0, size_descriptor_set,
                                       descriptor_set, 0, nullptr
            );
            for (auto const &push_constant: pipeline.get_push_constant_ranges()) {
                command.pushConstants(pipeline.get_pipeline_layout(),
                                      push_constant.stageFlags, push_constant.offset,
                                      push_constant.size,
                                      &rotation);
            }

            command.drawIndexed(vertex.get_indices_count(), 1, 0, 0, 0);
            command.nextSubpass(vk::SubpassContents::eInline);
        });
    };
    record(rotate());

    std::vector<mountain::buffer::uniform_updater> updaters;
    updaters.emplace_back(uniform_vp.get_uniform_updater(create_vp_matrix(width, height)));
    while (!glfwWindowShouldClose(context.get_window().get_window())) {
        glfwPollEvents();
        init.drawFrame(std::move(updaters));
        record(rotate());
    }
    vkDeviceWaitIdle(context.get_device());

    return 0;
}
