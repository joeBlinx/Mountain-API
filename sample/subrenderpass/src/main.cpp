#include "mountain/context.h"
#include "constant.h"
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

void key_callback(GLFWwindow *window, int key, int, int action, int) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    mountain::Window const window{"Subrendpass sample", constant::width, constant::height};
    mountain::Context const context{window, constant::devicesExtension};

    mountain::RenderPass const render_pass{context,
                                           {mountain::RenderPass::COLOR | mountain::RenderPass::DEPTH},
                                           {first_subpass()}
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
    mountain::GraphicsPipeline back_pipeline = mountain::PipelineBuilder(context)
            .create_color_blend_state()
            .create_mutlisampling()
            .create_rasterizer(vk::PolygonMode::eFill)
            .create_assembly(vk::PrimitiveTopology::eTriangleList)
            .create_viewport_info(swap_chain.get_swap_chain_extent())
            .create_vertex_info(quad_vertex_buffer)
            .create_depth_stencil_state(depth_stencil)
            .define_subpass(mountain::SubPass{&render_pass, 0})
            .create_shaders_info(std::vector{
                    mountain::shader{SHADER_FOLDER / "portraitvert.spv", vk::ShaderStageFlagBits::eVertex},
                    mountain::shader{SHADER_FOLDER / "portraitfrag.spv", vk::ShaderStageFlagBits::eFragment}
            })
            .create_pipeline_layout({}, vertex_push_constant)
            .build();

    mountain::CommandBuffer command_buffer(context, swap_chain, render_pass);
    command_buffer.record([&](mountain::CommandBuffer const &command_buffer, std::size_t const index) {
        vk::DeviceSize const offset(0);
        auto const &command = command_buffer.get_command_buffer(index);
        command.bindPipeline(vk::PipelineBindPoint::eGraphics, back_pipeline.get_pipeline());
        command.bindVertexBuffers(0, 1, &quad_vertex_buffer.get_buffer(), &offset);
        command.bindIndexBuffer(quad_vertex_buffer.get_buffer(), quad_vertex_buffer.get_indices_offset(),
                                vk::IndexType::eUint32);
        auto const& push_vertex = back_pipeline.get_push_constant(vk::ShaderStageFlagBits::eVertex);
        glm::mat4 model = glm::scale(glm::translate(glm::mat4{1.}, glm::vec3{0., 0, .5}), glm::vec3{0.5f});
        command.pushConstants(back_pipeline.get_pipeline_layout(), push_vertex.stageFlags,
                              push_vertex.offset, push_vertex.size, reinterpret_cast<std::byte const*>(&model));
        command.drawIndexed(quad_vertex_buffer.get_indices_count(), 1, 0, 0, 0);
        model = glm::translate(glm::mat4{1.}, glm::vec3{0., 0, 0.4});
        command.pushConstants(back_pipeline.get_pipeline_layout(), push_vertex.stageFlags,
                              push_vertex.offset, push_vertex.size, reinterpret_cast<std::byte const*>(&model));
        command.drawIndexed(quad_vertex_buffer.get_indices_count(), 1, 0, 0, 0);
    });

    glfwSetKeyCallback(context.get_window().get_window(), key_callback);
    using namespace std::chrono_literals;
    while (!glfwWindowShouldClose(context.get_window().get_window())) {
        glfwPollEvents();
        command_buffer.drawFrame({});
        std::this_thread::sleep_for(17ms);
    }
    context->waitIdle();


}