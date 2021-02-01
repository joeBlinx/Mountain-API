
#include <vector>
#include <mountain/context.h>
#include <mountain/renderpass/renderPass.h>
#include <mountain/swapChain.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <mountain/buffer/vertex.h>
#include <mountain/graphics_pipeline.h>
#include <mountain/initVulkan.h>
#include <thread>
#include "ressource_paths.h"
void key_callback(GLFWwindow* window, int key, int , int action, int)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE){
        glfwSetWindowShouldClose(window, true);
    }
}
std::vector<mountain::buffer::vertex> create_buffers(mountain::Context const& context){
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
    std::array vertices{
            Vertex{{0.f, -0.5f}, {1.0f, 0.f, 0.f}}, // 1
            Vertex{{-0.25f, 0.f}, {0.0f, 1.f, 0.f}},// 2
            Vertex{{0.25f, 0.f}, {0.0f, 0.f, 1.f}} // 3
    };
    std::array indices{0, 1, 2};
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

    mountain::Context context{width,
                              height,
                              "Mountain-API Push Constant",
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

    auto const buffers = create_buffers(context);

    struct PushConstant{
        struct VertexPushConstant{
            glm::mat4 model;
        }vertex_push_constant;
        struct FragmentPushConstant{
            float color;
        }fragment_push_constant;
    };
    mountain::PushConstant<PushConstant::VertexPushConstant> vertex_push{
        vk::ShaderStageFlagBits::eVertex
    };
    mountain::PushConstant<PushConstant::FragmentPushConstant> frag_push{
        vk::ShaderStageFlagBits::eFragment
    };
    mountain::GraphicsPipeline pipeline(context,
                                        swap_chain,
                                        render_pass,
                                        std::array{
                                                mountain::shader{SHADER_FOLDER / "push_constantvert.spv", vk::ShaderStageFlagBits::eVertex},
                                                mountain::shader{SHADER_FOLDER / "push_constantfrag.spv", vk::ShaderStageFlagBits::eFragment}
                                        },
                                        buffers, {}, vertex_push, frag_push);
    mountain::InitVulkan init(
            context,
            swap_chain,
            render_pass);

    glfwSetKeyCallback(context.get_window().get_window(), key_callback);

    mountain::PipelineData<PushConstant> object{
            buffers[0], pipeline, {PushConstant{
                glm::scale(
                        glm::vec3{2.0f}),
                       {0.5f}}
            }
    };
    init.createCommandBuffers(object);
    using namespace std::chrono_literals;
    int illuminance = 0;
    while (!glfwWindowShouldClose(context.get_window().get_window())) {
        glfwPollEvents();
        illuminance = (illuminance + 2) % 255;
        auto &push_constant = object.push_constant_values[0];
        push_constant.fragment_push_constant.color = static_cast<float>(illuminance / 255.0f);
        // because we use push constant we have to rebuild the command buffer each time we want
        // to modify our push constant value
        init.createCommandBuffers(object);
        init.drawFrame({});
        std::this_thread::sleep_for(17ms);
    }
    vkDeviceWaitIdle(context.get_device());

}