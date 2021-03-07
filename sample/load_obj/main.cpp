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
#include <mountain/load_model.h>
#include "ressource_paths.h"
#include "GLFW/glfw3.h"
#include "glm/gtx/transform.hpp"

struct Model{
    glm::mat4 model {1};
};

struct VP{
    glm::mat4 view{1.};
    glm::mat4 proj{1.};
};
void key_callback(GLFWwindow* window, int key, int , int action, int)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE){
        glfwSetWindowShouldClose(window, true);
    }
}
mountain::buffer::vertex create_quad_buffers_with_uv(mountain::Context const& context){

    auto [vertices_3d, indices_3d] = mountain::model::load_obj(std::filesystem::path(ASSETS_FOLDER /                                                                             "model/viking_room.obj"));
    return mountain::buffer::vertex(context,
                                    mountain::buffer::vertex_description(0, 0,
                                                                         mountain::model::Vertex::get_format_offsets()),
                                    vertices_3d,
                                    std::move(indices_3d));
}
VP create_vp_matrix(int width, int height){


    VP ubo{};
    ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.proj = glm::perspective(glm::radians(45.0f),
                                static_cast<float>(width) / (float) height,
                                0.1f, 10.0f);
    ubo.proj[1][1] *= -1;

    return ubo;
}
vk::SubpassDependency create_subpassdependency(){
    vk::SubpassDependency dependency{};
    dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests;
    dependency.srcAccessMask = static_cast<vk::AccessFlagBits>(0);
    dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests;
    dependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite | vk::AccessFlagBits::eDepthStencilAttachmentWrite;
    return dependency;
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
            auto const& push_vertex = pipeline.get_push_constant(vk::ShaderStageFlagBits::eVertex);
            glm::mat4 const value{1.f};
            command.pushConstants(pipeline.get_pipeline_layout(),
                                  push_vertex.stageFlags,
                                  push_vertex.offset,
                                  push_vertex.size, &value);
            command.drawIndexed(buffer.get_indices_count(), 1, 0, 0, 0);
        };
    }
    mountain::buffer::vertex const& buffer;
    mountain::GraphicsPipeline const& pipeline;
};

int main() {
	
	std::vector<const char*> const devicesExtension{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	int constexpr width = 1366;
	int constexpr height = 768;
    mountain::Window const window{"Mountain-API load obj sample\"", width, height};
    mountain::Context const context{window,
                                    devicesExtension};

    mountain::RenderPass const render_pass{
            context,
            {mountain::RenderPass::COLOR | mountain::RenderPass::DEPTH},
            {create_subpassdependency()}
    };

    mountain::SwapChain const swap_chain{
            context,
            render_pass,
            width,
            height
    };

    auto const vertex_buffer = create_quad_buffers_with_uv(context);

    mountain::PushConstant<Model> const push_vertex{
		vk::ShaderStageFlagBits::eVertex
	};

    vk::DescriptorSetLayoutBinding const ubo_binding_layout =
            mountain::descriptorset_layout::create_descriptor_uniform(2, vk::ShaderStageFlagBits::eVertex);

    vk::DescriptorSetLayoutBinding const image_sampler_layout =
            mountain::descriptorset_layout::create_descriptor_image_sampler(1, vk::ShaderStageFlagBits::eFragment);

    vk::DescriptorSetLayout const descriptor_layout = mountain::descriptorset_layout::create_descriptorset_layout(
            context, {ubo_binding_layout, image_sampler_layout}
            );

    mountain::buffer::image2d const statue_image{context, ASSETS_FOLDER / "image/statue.jpg", 1};
    mountain::buffer::image2d const viking_image{context, ASSETS_FOLDER /"image/viking_room.png", 10};
    mountain::image::sampler const sampler(context, viking_image.get_mimap_levels());
    auto layouts = std::vector{descriptor_layout};
    auto const depth_stencil = []{
        vk::PipelineDepthStencilStateCreateInfo info{};
        info.depthTestEnable = VK_TRUE;
        info.depthWriteEnable = VK_TRUE;
        info.depthCompareOp = vk::CompareOp::eLess;
        info.stencilTestEnable = VK_FALSE;
        return info;
    }();

    mountain::GraphicsPipeline const pipeline = mountain::PipelineBuilder(context)
            .create_assembly(vk::PrimitiveTopology::eTriangleList)
            .create_rasterizer(vk::PolygonMode::eFill)
            .create_mutlisampling()
            .create_color_blend_state()
            .create_vertex_info(vertex_buffer)
            .create_viewport_info(swap_chain.get_swap_chain_extent())
            .create_shaders_info(std::array{
                    mountain::shader{SHADER_FOLDER / "trianglevert.spv", vk::ShaderStageFlagBits::eVertex},
                    mountain::shader{SHADER_FOLDER / "trianglefrag.spv", vk::ShaderStageFlagBits::eFragment}
            })
            .create_depth_stencil_state(depth_stencil)
            .create_pipeline_layout(layouts, push_vertex)
            .define_subpass(mountain::SubPass{&render_pass, 0})
            .build();

    CommandBufferRecord record{
            .buffer = vertex_buffer,
            .pipeline = pipeline};

    mountain::CommandBuffer init(
            context,
            swap_chain,
            render_pass, 2);


    init.allocate_descriptor_set(std::move(layouts));
    mountain::buffer::uniform<VP> uniform_vp(context, swap_chain.get_swap_chain_image_views().size());

    init.update_descriptor_set(0, 2, uniform_vp);

    init.update_descriptor_set(0, 1, viking_image, sampler);

    glfwSetKeyCallback(context.get_window().get_window(), key_callback);

    init.record(record());
    std::vector<mountain::buffer::uniform_updater> updaters;
    updaters.emplace_back(uniform_vp.get_uniform_updater(create_vp_matrix(width, height)));
    while (!glfwWindowShouldClose(context.get_window().get_window())) {
        glfwPollEvents();
        init.drawFrame(std::move(updaters));
    }
    vkDeviceWaitIdle(context.get_device());

	return 0;
}
