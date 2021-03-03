
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
#include <mountain/descriptorset_layout.h>
#include "ressource_paths.h"
#include "GLFW/glfw3.h"
#include "glm/gtx/transform.hpp"

void key_callback(GLFWwindow* window, int key, int , int action, int)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE){
        glfwSetWindowShouldClose(window, true);
    }
}
mountain::buffer::vertex create_buffers(mountain::Context const& context){
    struct Vertex{
        glm::vec2 pos; // location 0
        glm::vec2 uv; // location 1
        static auto get_description() {
            return mountain::get_format_offsets(&Vertex::pos, &Vertex::uv);
        }
    };
    /* This is a triangle that will be shown
     *                 0       1
     *                 |------|
     *                 |      |
     *                 |      |
     *                 |      |
     *               2 |______|3
     */
    std::array constexpr vertices{
            Vertex{{-0.5f, -0.5f}, {0.0f, 0.f}}, // 0
            Vertex{{0.5f, -0.5f}, {1.0f, 0.f}},// 1
            Vertex{{-0.5f, 0.5f}, {0.0f, 1.f}},// 2
            Vertex{{0.5f, 0.5f}, {1.0f, 1.f}} // 3
    };
    std::array<uint32_t, 6> constexpr indices{0, 1, 2, 1, 2, 3};
    std::vector<mountain::buffer::vertex> buffers;

    return mountain::buffer::vertex{context,
                                    mountain::buffer::vertex_description(0,
                                                                         0,
                                                                         Vertex::get_description()),
                                    vertices,
                                    indices};
}

struct CommandBufferRecord{
    auto operator()(){
        return [&](mountain::CommandBuffer const& command_buffer, std::size_t const index){
            auto const& command = command_buffer.get_command_buffer(index);
            vk::DeviceSize constexpr size{0};
            command.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline.get_pipeline());
            command.bindVertexBuffers(0, 1, &buffer.get_buffer(), &size);
            command.bindIndexBuffer(buffer.get_buffer(), buffer.get_indices_offset(), vk::IndexType::eUint32);
            auto const [descriptor_set, number_descriptor] = command_buffer.get_descriptor_set_size(index);
            command.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipeline.get_pipeline_layout(), 0, number_descriptor,
                                       descriptor_set, 0, nullptr);
            command.drawIndexed(buffer.get_indices_count(), 1, 0, 0, 0);
        };
    }
    mountain::buffer::vertex const& buffer;
    mountain::GraphicsPipeline const& pipeline;
};
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

    auto const buffer = create_buffers(context);

    auto const layout_image = mountain::descriptorset_layout::create_descriptor_image_sampler(0, vk::ShaderStageFlagBits::eFragment);
    auto const descriptor_set = mountain::descriptorset_layout::create_descriptorset_layout(context, {layout_image});
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
                    mountain::shader{SHADER_FOLDER / "texturevert.spv", vk::ShaderStageFlagBits::eVertex},
                    mountain::shader{SHADER_FOLDER / "texturefrag.spv", vk::ShaderStageFlagBits::eFragment}
            })
            .create_depth_stencil_state(depth_stencil)
            .create_pipeline_layout(std::array{descriptor_set})
            .define_subpass(mountain::SubPass{&render_pass, 0})
            .build();

    CommandBufferRecord record{
            .buffer = buffer,
            .pipeline = pipeline};

    mountain::buffer::image2d const statue_image(context, ASSETS_FOLDER / "image/statue.jpg", 1);
    mountain::image::sampler const sampler(context, 1);
    mountain::CommandBuffer command_buffer(
            context,
            swap_chain,
            render_pass, 1);

    command_buffer.allocate_descriptor_set({descriptor_set});
    command_buffer.update_descriptor_set(0, 0, statue_image, sampler);
    glfwSetKeyCallback(context.get_window().get_window(), key_callback);

    command_buffer.record(record());
    using namespace std::chrono_literals;
    while (!glfwWindowShouldClose(context.get_window().get_window())) {
        glfwPollEvents();
        command_buffer.drawFrame({});
        std::this_thread::sleep_for(17ms);
    }
    context->waitIdle();

}
