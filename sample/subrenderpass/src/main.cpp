#include "mountain/context.h"
#include "common/constant.h"
#include "mountain/render_pass.h"
#include "mountain/swapChain.h"
#include "init.h"
#include "mountain/pipeline_builder.h"
#include "mountain/graphics_pipeline.h"
#include "ressource_paths.h"
#include "mountain/command_buffer.h"
#include "GLFW/glfw3.h"
#include <thread>
#include <glm/gtx/transform.hpp>
#include <mountain/present.h>
void key_callback(GLFWwindow *window, int key, int, int action, int) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    mountain::Window const window{"Subrendpass sample", constant::width, constant::height};
    mountain::Context const context(window, constant::devicesExtension);

    mountain::RenderPass const render_pass{context,
                                           {mountain::RenderPass::COLOR | mountain::RenderPass::DEPTH,
                                            mountain::RenderPass::COLOR | mountain::RenderPass::DEPTH},
                                           {first_subpass(),
                                            first_subpass()}
    };

    mountain::SwapChain const swap_chain(context,
                                         render_pass,
                                         constant::width,
                                         constant::height
    );
    auto const quad_vertex_buffer = create_quad_vertex_buffer(context);
    auto const depth_stencil = [] {
        vk::PipelineDepthStencilStateCreateInfo info{};
        info.depthTestEnable = VK_TRUE;
        info.depthWriteEnable = VK_TRUE;
        info.depthCompareOp = vk::CompareOp::eLess;
        info.stencilTestEnable = VK_FALSE;
        return info;
    }();
    mountain::PushConstant<glm::mat4> vertex_push_constant{vk::ShaderStageFlagBits::eVertex};
    mountain::GraphicsPipeline const back_pipeline = mountain::PipelineBuilder(context)
            .create_assembly(vk::PrimitiveTopology::eTriangleList)
            .create_rasterizer(vk::PolygonMode::eFill)
            .create_viewport_info(swap_chain.get_swap_chain_extent())
            .create_depth_stencil_state(depth_stencil)
            .create_color_blend_state()
            .create_shaders_info(std::vector{
                    mountain::shader{SHADER_FOLDER / "portraitvert.spv", vk::ShaderStageFlagBits::eVertex},
                    mountain::shader{SHADER_FOLDER / "portraitfrag.spv", vk::ShaderStageFlagBits::eFragment}
            })
            .create_vertex_info(quad_vertex_buffer)
            .create_mutlisampling()
            .define_subpass(mountain::SubPass{&render_pass, 0})
            .create_pipeline_layout({}, vertex_push_constant)
            .build();

    auto const depth_stencil2 = [] {
        vk::PipelineDepthStencilStateCreateInfo info{};
        info.depthTestEnable = VK_FALSE;
        info.depthWriteEnable = VK_FALSE;
        info.depthCompareOp = vk::CompareOp::eLess;
        info.stencilTestEnable = VK_FALSE;
        return info;
    }();
    mountain::GraphicsPipeline front_pipeline = mountain::PipelineBuilder(context)
            .create_assembly(vk::PrimitiveTopology::eTriangleList)
            .create_rasterizer(vk::PolygonMode::eFill)
            .create_viewport_info(swap_chain.get_swap_chain_extent())
            .create_depth_stencil_state(depth_stencil2)
            .create_color_blend_state()
            .create_shaders_info(std::vector{
                    mountain::shader{SHADER_FOLDER / "portraitvert.spv", vk::ShaderStageFlagBits::eVertex},
                    mountain::shader{SHADER_FOLDER / "portraitfrag.spv", vk::ShaderStageFlagBits::eFragment}
            })
            .create_vertex_info(quad_vertex_buffer)
            .create_mutlisampling()
            .define_subpass(mountain::SubPass{&render_pass, 1})
            .create_pipeline_layout({}, vertex_push_constant)
            .build();

    mountain::CommandBuffer command_buffer(context, swap_chain, render_pass);
    command_buffer.record(CommandBufferRecorded{
        .back_pipeline = back_pipeline,
        .front_pipeline = front_pipeline,
        .quad_vertex_buffer = quad_vertex_buffer
    });

    glfwSetKeyCallback(context.get_window().get_window(), key_callback);
    using namespace std::chrono_literals;
    mountain::Present present{context, swap_chain};
    while (!glfwWindowShouldClose(context.get_window().get_window())) {
        glfwPollEvents();
        present(command_buffer);
        std::this_thread::sleep_for(17ms);
    }
    context->waitIdle();


}