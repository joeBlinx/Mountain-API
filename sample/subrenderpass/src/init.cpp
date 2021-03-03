//
// Created by stiven on 3/2/21.
//

#include <glm/gtx/transform.hpp>
#include "init.h"
namespace color{
    glm::vec4 constexpr RED {1., 0, 0, 1.};
    glm::vec4 constexpr GREEN {0., 1., 0, 1.};
    glm::vec4 constexpr BLUE {0., 0., 1., 1.};
    glm::vec4 constexpr WHITE {1., 1, 1, 1.};
    glm::vec4 constexpr BLACK {0., 0, 0, 1.};
}
vk::SubpassDependency first_subpass(){
    return []{
        vk::SubpassDependency dependency{};
        dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
        dependency.srcAccessMask = static_cast<vk::AccessFlagBits>(0);
        dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput |vk::PipelineStageFlagBits::eEarlyFragmentTests;
        dependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite |vk::AccessFlagBits::eDepthStencilAttachmentWrite;
        return dependency;
    }();
}
mountain::buffer::vertex create_quad_vertex_buffer(mountain::Context const& context){
    std::array constexpr vertex{
        VertexWithColor{{-0.5, -0.5, 0.0},{color::RED}},
        VertexWithColor{{0.5, -0.5, 0.0},{color::GREEN}},
        VertexWithColor{{-0.5, 0.5, 0.0},{color::BLUE}},
        VertexWithColor{{0.5, 0.5, 0.0},{color::WHITE}},
    };

    return {context,
            mountain::buffer::vertex_description(0, 0, VertexWithColor::get_format_offset()),
            vertex,
            std::array{0u, 1u, 2u, 1u, 2u, 3u}
    };
}

void CommandBufferRecorded::operator()(const mountain::CommandBuffer &command_buffer, const std::size_t index) {
    vk::DeviceSize const offset(0);
    auto const &command = command_buffer.get_command_buffer(index);
    command.bindPipeline(vk::PipelineBindPoint::eGraphics, back_pipeline.get_pipeline());
    command.bindVertexBuffers(0, 1, &quad_vertex_buffer.get_buffer(), &offset);
    command.bindIndexBuffer(quad_vertex_buffer.get_buffer(), quad_vertex_buffer.get_indices_offset(),
                            vk::IndexType::eUint32);
    auto const& push_vertex = back_pipeline.get_push_constant(vk::ShaderStageFlagBits::eVertex);
    glm::mat4 model = glm::translate(glm::mat4{1.}, glm::vec3{0., 0, 0.3});
    command.pushConstants(back_pipeline.get_pipeline_layout(), push_vertex.stageFlags,
                          push_vertex.offset, push_vertex.size, reinterpret_cast<std::byte const*>(&model));
    command.drawIndexed(quad_vertex_buffer.get_indices_count(), 1, 0, 0, 0);
    model = glm::translate(glm::mat4{1.}, glm::vec3{0., 0, 0.4});
    model = glm::scale(glm::translate(glm::mat4{1.}, glm::vec3{0., 0, .5}), glm::vec3{0.5f});

    command.nextSubpass(vk::SubpassContents::eInline);
    command.bindPipeline(vk::PipelineBindPoint::eGraphics, front_pipeline.get_pipeline());
    command.bindVertexBuffers(0, 1, &quad_vertex_buffer.get_buffer(), &offset);
    command.bindIndexBuffer(quad_vertex_buffer.get_buffer(), quad_vertex_buffer.get_indices_offset(),
                            vk::IndexType::eUint32);
    command.pushConstants(front_pipeline.get_pipeline_layout(), push_vertex.stageFlags,
                          push_vertex.offset, push_vertex.size, reinterpret_cast<std::byte const*>(&model));
    command.drawIndexed(quad_vertex_buffer.get_indices_count(), 1, 0, 0, 0);
}
