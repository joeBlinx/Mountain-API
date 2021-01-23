
#include <vector>
#include <mountain/context.hpp>
#include <mountain/renderpass/renderPass.hpp>
#include <mountain/swapChain.hpp>
#include <glm/glm.hpp>
#include <mountain/buffer/vertex.hpp>
#include <mountain/graphics_pipeline.hpp>
#include <mountain/initVulkan.hpp>
#include <thread>
#include "ressource_paths.h"
#include "mountain/descriptor_setlayout_binding/descriptorset_layout.h"
void key_callback(GLFWwindow* window, int key, int , int action, int)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE){
        glfwSetWindowShouldClose(window, true);
    }
}
int main(){

    std::vector<const char*> const devicesExtension{
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    int constexpr width = 1366;
    int constexpr height = 768;

    mountain::Context context{width,
                    height,
                    "Mountain-API Triangle",
                    devicesExtension};

    using mountain::subpass_attachment;
    mountain::RenderPass render_pass{
            context,
            mountain::SubPass{subpass_attachment::COLOR}
    };

    mountain::SwapChain swap_chain{
            context,
            render_pass,
            vk::ImageUsageFlagBits::eColorAttachment,
            width,
            height
    };
    struct Vertex{
        glm::vec2 pos; // location 0
        glm::vec2 uv; // location 1
    };
    /* This is a triangle that will be shown
     *                    1 (0., -0.5f) don't forget that the y axis
     *                   /\ // is from top to bottom
     *                  /  \
     *                 /    \
     * (-0.25, 0)    2 ______ 3 (0.25, 0.)
     */
    std::vector<Vertex> vertices{
            Vertex{{-0.5f, -0.5f}, {0.f, 0.f}}, // 1
            Vertex{{0.5f, -0.5f}, {1.0f, 0.f}},// 2
            Vertex{{-0.5f, 0.5f}, {0.0f, 1.f}}, // 3
            Vertex{{0.5f, 0.5f}, {1.0f, 1.f}}, // 4
    };
    std::vector<uint32_t> indices{0, 1, 2};
    std::vector<mountain::buffer::vertex> buffers;
    buffers.emplace_back(
            mountain::buffer::vertex{context,
                         mountain::buffer::vertex_description(0,
                                                  0,
                                                  CLASS_DESCRIPTION(Vertex, uv, pos)),
                                  vertices,
                                  std::move(indices)}
    );

    auto descriptor_image = mountain::descriptorset_layout::create_descriptor_image_sampler(0, vk::ShaderStageFlagBits::eFragment);
    auto image_layout = mountain::descriptorset_layout::create_descriptorset_layout(context, {descriptor_image});
    std::vector layouts{image_layout};
    mountain::GraphicsPipeline pipeline(context,
                              swap_chain,
                              render_pass,
                              std::array{
                                      mountain::shader{SHADER_FOLDER / "trianglevert.spv", vk::ShaderStageFlagBits::eVertex},
                                      mountain::shader{SHADER_FOLDER / "trianglefrag.spv", vk::ShaderStageFlagBits::eFragment}
                              },
                              buffers, layouts);
    mountain::buffer::image2d texture (context, ASSETS_FOLDER / "image/statue.jpg", 0);
    mountain::image::sampler sampler(context, 0);
    mountain::InitVulkan init(
            context,
            swap_chain,
            render_pass, 1);
    init.allocate_descriptor_set(std::move(layouts));
    init.update_descriptor_set(0, 0, texture, sampler);
    glfwSetKeyCallback(context.get_window().get_window(), key_callback);
    struct no_uni{};
    mountain::PipelineData<no_uni> object{
        buffers[0], pipeline, {}
    };
    init.createCommandBuffers(object);
    using namespace std::chrono_literals;
    while (!glfwWindowShouldClose(context.get_window().get_window())) {
        glfwPollEvents();
        init.drawFrame({});
        std::this_thread::sleep_for(17ms);
    }
    vkDeviceWaitIdle(context.get_device());

}