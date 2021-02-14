
#include <vector>
#include "mountain/context.h"
#include "mountain/render_pass.h"
#include "mountain/swapChain.h"
#include <glm/glm.hpp>
#include "mountain/vertex.h"
#include "mountain/graphics_pipeline.h"
#include "mountain/command_buffer.h"
#include <thread>
#include "ressource_paths.h"
#include "mountain/descriptorset_layout.h"
void key_callback(GLFWwindow* window, int key, int , int action, int)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE){
        glfwSetWindowShouldClose(window, true);
    }
}
std::vector<mountain::buffer::vertex> create_buffers(mountain::Context const& context){
    struct Vertex{
        glm::vec2 pos; // location 0
        glm::vec2 uv; // location 1
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
    buffers.emplace_back(
            mountain::buffer::vertex{context,
                                     mountain::buffer::vertex_description(0,
                                                                          0,
                                                                          CLASS_DESCRIPTION(Vertex, uv, pos)),
                                     vertices,
                                     indices}
    );
    return buffers;
}
int main(){

    std::vector<const char*> const devicesExtension{
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    int constexpr width = 1366;
    int constexpr height = 768;

    mountain::Window const window{"Mountain-API Texture Square", width, height};
    mountain::Context const context{window,
                                    devicesExtension};

    using mountain::subpass_attachment;
    mountain::RenderPass const render_pass{
            context,
            mountain::SubPass{subpass_attachment::COLOR}
    };

    mountain::SwapChain const swap_chain{
            context,
            render_pass,
            width,
            height
    };

    std::vector<mountain::buffer::vertex> const buffers = create_buffers(context);

    auto const layout_image = mountain::descriptorset_layout::create_descriptor_image_sampler(0, vk::ShaderStageFlagBits::eFragment);
    auto const descriptor_set = mountain::descriptorset_layout::create_descriptorset_layout(context, {layout_image});
    mountain::GraphicsPipeline const pipeline(context,
                              swap_chain,
                              render_pass,
                              std::array{
                                      mountain::shader{SHADER_FOLDER / "texturevert.spv", vk::ShaderStageFlagBits::eVertex},
                                      mountain::shader{SHADER_FOLDER / "texturefrag.spv", vk::ShaderStageFlagBits::eFragment}
                              },
                              buffers, {descriptor_set});
    mountain::buffer::image2d const statue_image(context, ASSETS_FOLDER / "image/statue.jpg", 1);
    mountain::image::sampler const sampler(context, 1);
    mountain::CommandBuffer init(
            context,
            swap_chain,
            render_pass, 1);
    init.allocate_descriptor_set({descriptor_set});
    init.update_descriptor_set(0, 0, statue_image, sampler);
    glfwSetKeyCallback(context.get_window().get_window(), key_callback);
    struct no_uni{};
    mountain::PipelineData<no_uni> object{
        buffers[0], pipeline, {}
    };
    init.init(object);
    using namespace std::chrono_literals;
    while (!glfwWindowShouldClose(context.get_window().get_window())) {
        glfwPollEvents();
        init.drawFrame({});
        std::this_thread::sleep_for(17ms);
    }
    vkDeviceWaitIdle(context.get_device());

}