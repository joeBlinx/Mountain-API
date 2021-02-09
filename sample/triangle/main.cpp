
#include <vector>
#include <mountain/context.h>
#include <mountain/renderpass/render_pass.h>
#include <mountain/swapChain.h>
#include <glm/glm.hpp>
#include <mountain/buffer/vertex.h>
#include <mountain/graphics_pipeline.h>
#include <mountain/command_buffer.h>
#include <thread>
#include "ressource_paths.h"
void key_callback(GLFWwindow* window, int key, int , int action, int)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE){
        glfwSetWindowShouldClose(window, true);
    }
}
std::vector<mountain::buffer::vertex> create_vertex(mountain::Context const& context){
    struct Vertex{
        glm::vec2 pos; // location 0
        glm::vec3 color; // location 1
    };
    /* This is a triangle that will be shown
     *                    1 (0., -0.5f) don't forget that the y axis
     *                   /\ // is from top to bottom
     *                  /  \
     *                 /    \
     * (-0.25, 0)    2 ______ 3 (0.25, 0.)
     */
    std::array constexpr vertices{
            Vertex{{0.f, -0.5f}, {1.0f, 0.f, 0.f}}, // 1
            Vertex{{-0.25f, 0.f}, {0.0f, 1.f, 0.f}},// 2
            Vertex{{0.25f, 0.f}, {0.0f, 0.f, 1.f}} // 3
    };
    std::array<uint32_t, 3> constexpr indices{0, 1, 2};
    std::vector<mountain::buffer::vertex> buffers;
    buffers.emplace_back(
            mountain::buffer::vertex{context,
                                     mountain::buffer::vertex_description(0,
                                                                          0,
                                                                          CLASS_DESCRIPTION(Vertex, color, pos)),
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

    mountain::Context const context{width,
                    height,
                    "Vulkan Triangle",
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

    std::vector<mountain::buffer::vertex> const buffers = create_vertex(context);

    mountain::GraphicsPipeline const pipeline(context,
                              swap_chain,
                              render_pass,
                              std::array{
                                      mountain::shader{SHADER_FOLDER / "trianglevert.spv", vk::ShaderStageFlagBits::eVertex},
                                      mountain::shader{SHADER_FOLDER / "trianglefrag.spv", vk::ShaderStageFlagBits::eFragment}
                              },
                              buffers);
    mountain::CommandBuffer command_buffer(
            context,
            swap_chain,
            render_pass);

    glfwSetKeyCallback(context.get_window().get_window(), key_callback);
    struct no_uni{};
    mountain::PipelineData<no_uni> object{
        buffers[0], pipeline, {}
    };
    command_buffer.init(object);
    using namespace std::chrono_literals;
    while (!glfwWindowShouldClose(context.get_window().get_window())) {
        glfwPollEvents();
        command_buffer.drawFrame({});
        std::this_thread::sleep_for(17ms);
    }
    context->waitIdle();

}