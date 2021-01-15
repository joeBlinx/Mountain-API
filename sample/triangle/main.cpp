

#include <vector>
#include <sandbox_useful/context.hpp>
#include <sandbox_useful/renderpass/renderPass.hpp>
#include <sandbox_useful/swapChain.hpp>
#include <glm/glm.hpp>
#include <sandbox_useful/buffer/vertex.hpp>
#include <sandbox_useful/graphics_pipeline.hpp>
#include <sandbox_useful/initVulkan.hpp>

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

    Context context{width,
                    height,
                    "Vulkan Triangle",
                    devicesExtension};

    RenderPass render_pass{
            context,
            SubPass{subpass_attachment::COLOR}
    };

    SwapChain swap_chain{
            context,
            render_pass,
            vk::ImageUsageFlagBits::eColorAttachment,
            width,
            height
    };
    struct Vertex{
        glm::vec2 pos;
    };
    std::vector<Vertex> vertices{
            Vertex{{0.f, 0.5f}},
            Vertex{{-0.25f, 0.f}},
            Vertex{{0.25f, 0.f}}
    };
    std::vector<uint32_t> indices{0, 1, 2};
    std::vector<buffer::vertex> buffers;
    buffers.emplace_back(
        buffer::vertex{context,
                       buffer::vertex_description(0,
                                                  0,
                                                  CLASS_DESCRIPTION(Vertex, pos)),
                      vertices,
                      std::move(indices)}
    );
    GraphicsPipeline pipeline(context,
                              swap_chain,
                              render_pass,
                              std::array{
                                      shader{"trianglevert.spv", vk::ShaderStageFlagBits::eVertex},
                                      shader{"trianglefrag.spv", vk::ShaderStageFlagBits::eFragment}
                              },
                              buffers);
    InitVulkan init(
            context,
            swap_chain,
            render_pass);

    glfwSetKeyCallback(context.get_window().get_window(), key_callback);
    struct no_uni{};
    PipelineData<no_uni> object{
        buffers[0], pipeline, {}
    };
    init.createCommandBuffers(object);
    while (!glfwWindowShouldClose(context.get_window().get_window())) {
        glfwPollEvents();
        init.drawFrame({});
    }
    vkDeviceWaitIdle(context.get_device());

}