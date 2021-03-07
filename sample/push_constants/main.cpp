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
#include "glm/gtx/transform.hpp"
#include "common/init.h"
struct PushConstant{
    struct VertexPushConstant{
        glm::mat4 model{};
    }vertex_push_constant;
    struct FragmentPushConstant{
        float color{};
    }fragment_push_constant;
};
struct CommandBufferRecord{
    auto operator()(PushConstant const push_constant){
        return [&, push_constant](mountain::CommandBuffer const& command_buffer, std::size_t const index){
            auto const& command = command_buffer.get_command_buffer(index);
            vk::DeviceSize constexpr size{0};
            command.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline.get_pipeline());
            command.bindVertexBuffers(0, 1, &buffer.get_buffer(), &size);
            command.bindIndexBuffer(buffer.get_buffer(), buffer.get_indices_offset(), vk::IndexType::eUint32);
            auto const& push_vertex = pipeline.get_push_constant(vk::ShaderStageFlagBits::eVertex);
            command.pushConstants(pipeline.get_pipeline_layout(), push_vertex.stageFlags,
                                  push_vertex.offset,
                                  push_vertex.size,
                                  &push_constant.vertex_push_constant);
            auto const& push_fragment = pipeline.get_push_constant(vk::ShaderStageFlagBits::eFragment);
            command.pushConstants(pipeline.get_pipeline_layout(), push_fragment.stageFlags,
                                  push_fragment.offset,
                                  push_fragment.size,
                                  &push_constant.fragment_push_constant);
            command.drawIndexed(buffer.get_indices_count(), 1, 0, 0, 0);
        };
    }
    mountain::buffer::vertex const& buffer;
    mountain::GraphicsPipeline const& pipeline;
};
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

    mountain::PushConstant<PushConstant::VertexPushConstant> vertex_push{
            vk::ShaderStageFlagBits::eVertex
    };
    mountain::PushConstant<PushConstant::FragmentPushConstant> frag_push{
            vk::ShaderStageFlagBits::eFragment
    };
    mountain::GraphicsPipeline const pipeline = mountain::PipelineBuilder(context)
            .create_assembly(vk::PrimitiveTopology::eTriangleList)
            .create_rasterizer(vk::PolygonMode::eFill)
            .create_mutlisampling()
            .create_color_blend_state()
            .create_vertex_info(buffer)
            .create_viewport_info(swap_chain.get_swap_chain_extent())
            .create_shaders_info(std::array{
                    mountain::shader{SHADER_FOLDER / "push_constantvert.spv", vk::ShaderStageFlagBits::eVertex},
                    mountain::shader{SHADER_FOLDER / "push_constantfrag.spv", vk::ShaderStageFlagBits::eFragment}
            })
            .create_depth_stencil_state(depth_stencil)
            .create_pipeline_layout({}, vertex_push, frag_push)
            .define_subpass(mountain::SubPass{&render_pass, 0})
            .build();
    CommandBufferRecord record{
        .buffer = buffer,
        .pipeline = pipeline};

    mountain::CommandBuffer command_buffer(
            context,
            swap_chain,
            render_pass);


    glfwSetKeyCallback(context.get_window().get_window(), key_callback);
    int illuminance = 0;
    float size = 1.0f;
    float delta = 0.04f;
    using namespace std::chrono_literals;
    while (!glfwWindowShouldClose(context.get_window().get_window())) {
        glfwPollEvents();
        illuminance = (illuminance + 2) % 255;
        size += delta;
        if(size >= 1.0f || size <= 0.0f){
            delta *= -1;
        }
        command_buffer.record(record(PushConstant{
            .vertex_push_constant{glm::scale(glm::vec3{size})},
            .fragment_push_constant{static_cast<float>(illuminance)/255.0f}}));
        command_buffer.drawFrame({});
        std::this_thread::sleep_for(17ms);
    }
    context->waitIdle();

}