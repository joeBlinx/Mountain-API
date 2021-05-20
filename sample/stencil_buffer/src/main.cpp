//
// Created by stiven_perso on 3/7/21.
//


#include <mountain/command_buffer.h>
#include <mountain/pipeline_builder.h>
#include "common/constant.h"
#include "common/init.h"
#include "ressource_paths.h"
#include <array>
#include <thread>
#include <GLFW/glfw3.h>
#include "mountain/descriptorset_layout.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <search.h>
#include <mountain/present.h>
void key_callback(GLFWwindow* window, int key, int , int action, int)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE){
        glfwSetWindowShouldClose(window, true);
    }
}
auto first_subpass() {
    vk::SubpassDependency dependency{};
    dependency.srcAccessMask = static_cast<vk::AccessFlagBits>(0);
    dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
    dependency.dstAccessMask = vk::AccessFlagBits::eDepthStencilAttachmentWrite;
    dependency.dstStageMask =vk::PipelineStageFlagBits::eEarlyFragmentTests;
    return dependency;
}
auto second_subpass() {
    vk::SubpassDependency dependency{};
    dependency.srcAccessMask = vk::AccessFlagBits::eColorAttachmentRead|
            vk::AccessFlagBits::eDepthStencilAttachmentRead;
    dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput|
            vk::PipelineStageFlagBits::eEarlyFragmentTests;
    dependency.dstAccessMask = vk::AccessFlagBits::eDepthStencilAttachmentWrite
                               | vk::AccessFlagBits::eColorAttachmentWrite;
    dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput
            |vk::PipelineStageFlagBits::eEarlyFragmentTests;
    return dependency;
}
int main(){
    mountain::Window const window{"Stencil buffer", constant::width, constant::height};
    mountain::Context const context{window, constant::devicesExtension};

    mountain::RenderPass const render_pass{context,
                                           {mountain::RenderPass::COLOR | mountain::RenderPass::STENCIL,
                                            mountain::RenderPass::COLOR | mountain::RenderPass::STENCIL},
                                           {first_subpass(), second_subpass()}};

    mountain::SwapChain const swap_chain {context, render_pass, constant::width, constant::height};

    auto const stencil_first_subpass = []{
        vk::StencilOpState op_stencil{};
        op_stencil.compareOp = vk::CompareOp::eAlways;
        op_stencil.passOp = vk::StencilOp::eIncrementAndClamp;
        op_stencil.failOp = vk::StencilOp::eKeep;
        op_stencil.depthFailOp  = vk::StencilOp::eIncrementAndClamp;
        op_stencil.compareMask = 0xff;
        op_stencil.writeMask = 0xff;
        op_stencil.reference = 1;
        vk::PipelineDepthStencilStateCreateInfo stencil{};
        stencil.depthTestEnable = VK_TRUE;
        stencil.depthWriteEnable = VK_TRUE;
        stencil.depthCompareOp = vk::CompareOp::eNever;
        stencil.stencilTestEnable = VK_TRUE;
        stencil.front = op_stencil;
        stencil.back = vk::StencilOpState{};
        return stencil;
    }();
    auto const stencil_second_subpass = []{
        vk::StencilOpState op_stencil{};
        op_stencil.compareOp = vk::CompareOp::eLessOrEqual;
        op_stencil.passOp = vk::StencilOp::eIncrementAndClamp;
        op_stencil.failOp = vk::StencilOp::eKeep;
        op_stencil.depthFailOp  = vk::StencilOp::eKeep;
        op_stencil.compareMask = 0xff;
        op_stencil.writeMask = 0xff;
        op_stencil.reference = 1;
        vk::PipelineDepthStencilStateCreateInfo stencil{};
        stencil.stencilTestEnable = VK_TRUE;
        stencil.front = op_stencil;
        stencil.back = vk::StencilOpState{};
        return stencil;
    }();
    auto const vertex_buffer = create_quad_buffers_with_uv(context);
    auto const shaders = std::array{
            mountain::shader{SHADER_FOLDER / "stencil_buffervert.spv", vk::ShaderStageFlagBits::eVertex},
            mountain::shader{SHADER_FOLDER / "stencil_bufferfrag.spv", vk::ShaderStageFlagBits::eFragment}
    };
    mountain::buffer::image2d const statue{context, ASSETS_FOLDER/"image/statue.jpg", 1};
    mountain::image::sampler const sampler{context, 1};
    auto const image_descriptor = mountain::descriptorset_layout::create_descriptor_image_sampler (0, vk::ShaderStageFlagBits::eFragment);
    auto descriptors = std::vector{mountain::descriptorset_layout::create_descriptorset_layout(context, {image_descriptor})};
    const mountain::PushConstant<glm::mat4> model{
        vk::ShaderStageFlagBits::eVertex
    };
    mountain::GraphicsPipeline const pipeline = mountain::PipelineBuilder{context}
            .create_assembly(vk::PrimitiveTopology::eTriangleList)
                                                .create_rasterizer(vk::PolygonMode::eFill)
                                                .create_viewport_info(swap_chain.get_swap_chain_extent())
                                                .create_depth_stencil_state(stencil_first_subpass)
                                                .create_color_blend_state()
                                                .create_shaders_info(shaders)
                                                .create_vertex_info(vertex_buffer)
                                                .create_mutlisampling()
                                                .define_subpass(mountain::SubPass{&render_pass, 0})
                                                .create_pipeline_layout(descriptors, model)
                                                .build();

    mountain::GraphicsPipeline const pipeline2 = mountain::PipelineBuilder{context}
            .create_assembly(vk::PrimitiveTopology::eTriangleList)
            .create_rasterizer(vk::PolygonMode::eFill)
            .create_viewport_info(swap_chain.get_swap_chain_extent())
            .create_depth_stencil_state(stencil_second_subpass)
            .create_color_blend_state()
            .create_shaders_info(shaders)
            .create_vertex_info(vertex_buffer)
            .create_mutlisampling()
            .define_subpass(mountain::SubPass{&render_pass, 1})
            .create_pipeline_layout(descriptors, model)
            .build();

    mountain::CommandBuffer command_buffer {context, swap_chain, render_pass, 1};
    command_buffer.allocate_descriptor_set(std::move(descriptors));
    command_buffer.update_descriptor_set(0, 0, statue, sampler);
    command_buffer.record([&](mountain::CommandBuffer const& command_buffer, std::size_t const index){
        auto const& command = command_buffer.get_command_buffer(index);
        constexpr vk::DeviceSize offset{0};
        auto const [descriptor, size] = command_buffer.get_descriptor_set_size(index);

        command.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline.get_pipeline());
        command.bindVertexBuffers(0, 1, &vertex_buffer.get_buffer(), &offset);
        command.bindIndexBuffer(vertex_buffer.get_buffer(), vertex_buffer.get_indices_offset(), vk::IndexType::eUint32);
        command.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipeline.get_pipeline_layout(), 0, size,  descriptor, 0, nullptr);

        auto const push_vertex = pipeline.get_push_constant(vk::ShaderStageFlagBits::eVertex);
        auto const divide_by_2 = glm::scale(glm::mat4{1.}, glm::vec3{0.5});
        command.pushConstants(pipeline.get_pipeline_layout(), push_vertex.stageFlags,
                              push_vertex.offset,
                              push_vertex.size, &divide_by_2);
        command.drawIndexed(vertex_buffer.get_indices_count(), 1, 0, 0, 0);
        command.nextSubpass(vk::SubpassContents::eInline);

        command.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline2.get_pipeline());
        command.bindVertexBuffers(0, 1, &vertex_buffer.get_buffer(), &offset);
        command.bindIndexBuffer(vertex_buffer.get_buffer(), vertex_buffer.get_indices_offset(), vk::IndexType::eUint32);
        command.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipeline2.get_pipeline_layout(), 0, size,  descriptor, 0, nullptr);
        auto const identity = glm::mat4{1.};
        command.pushConstants(pipeline2.get_pipeline_layout(), push_vertex.stageFlags,
                              push_vertex.offset,
                              push_vertex.size, &identity);
        command.drawIndexed(vertex_buffer.get_indices_count(), 1, 0, 0, 0);

    });
    glfwSetKeyCallback(context.get_window().get_window(), key_callback);
    using namespace std::chrono_literals;
    mountain::Present present{context, swap_chain};
    while(!window.window_should_close()){
        glfwPollEvents();
        present(command_buffer);
        std::this_thread::sleep_for(17ms);
    }
    context->waitIdle();


}