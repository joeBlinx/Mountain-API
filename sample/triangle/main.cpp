
#include <vector>
#include "mountain/context.h"
#include "mountain/render_pass.h"
#include "mountain/swapChain.h"
#include <glm/glm.hpp>
#include "mountain/vertex.h"
#include "mountain/graphics_pipeline.h"
#include "mountain/command_buffer.h"
#include <thread>
#include <mountain/pipeline_builder.h>
#include "ressource_paths.h"
#include "GLFW/glfw3.h"
#include "common/init.h"
void key_callback(GLFWwindow* window, int key, int , int action, int)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE){
        glfwSetWindowShouldClose(window, true);
    }
}

vk::SubpassDependency create_subpassdependency(){
    vk::SubpassDependency dependency{};
    dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
    dependency.srcAccessMask = static_cast<vk::AccessFlagBits>(0);
    dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
    dependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;
    return dependency;
}
int main(){

    std::vector<const char*> const devicesExtension{
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    int constexpr width = 1366;
    int constexpr height = 768;
    mountain::Window const window{"Vulkan Triangle", width, height};
    mountain::Context const context{window,
                    devicesExtension};

    mountain::RenderPass const render_pass{
            context,
            {mountain::RenderPass::COLOR},
            {create_subpassdependency()}
    };

    mountain::SwapChain const swap_chain{
            context,
            render_pass,
            width,
            height
    };

    auto const buffer = create_triangle_buffer_with_color(context);
    auto const depth_stencil = []{
        vk::PipelineDepthStencilStateCreateInfo info{};
        info.depthTestEnable = VK_FALSE;
        info.stencilTestEnable = VK_FALSE;
        return info;
    }();
    mountain::GraphicsPipeline const pipeline = mountain::PipelineBuilder(context)
            .create_assembly(vk::PrimitiveTopology::eTriangleList)
            .create_rasterizer(vk::PolygonMode::eFill)
            .create_mutlisampling()
            .create_color_blend_state()
            .create_vertex_info(buffer)
            .create_viewport_info(swap_chain.get_swap_chain_extent())
            .create_shaders_info(std::array{
                    mountain::shader{SHADER_FOLDER / "trianglevert.spv", vk::ShaderStageFlagBits::eVertex},
                    mountain::shader{SHADER_FOLDER / "trianglefrag.spv", vk::ShaderStageFlagBits::eFragment}
            })
            .create_depth_stencil_state(depth_stencil)
            .create_pipeline_layout({})
            .define_subpass(mountain::SubPass{&render_pass, 0})
            .build();

    mountain::CommandBuffer command_buffer(
            context,
            swap_chain,
            render_pass);

    command_buffer.record([&](mountain::CommandBuffer const& command_buffer, std::size_t const index){
       auto const& command = command_buffer.get_command_buffer(index);
       vk::DeviceSize constexpr size{0};
       command.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline.get_pipeline());
       command.bindVertexBuffers(0, 1, &buffer.get_buffer(), &size);
       command.bindIndexBuffer(buffer.get_buffer(), buffer.get_indices_offset(), vk::IndexType::eUint32);
       command.drawIndexed(buffer.get_indices_count(), 1, 0, 0, 0);
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