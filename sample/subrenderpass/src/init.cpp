//
// Created by stiven on 3/2/21.
//

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
        dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
        dependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;
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