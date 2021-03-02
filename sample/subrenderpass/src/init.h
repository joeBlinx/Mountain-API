//
// Created by stiven on 3/2/21.
//

#ifndef MOUNTAIN_API_INIT_H
#define MOUNTAIN_API_INIT_H
#include <vulkan/vulkan.hpp>
#include <glm/glm.hpp>
#include "mountain/vertex.h"

vk::SubpassDependency first_subpass();

struct VertexWithColor{
    glm::vec3 pos;
    glm::vec4 color;
    static auto get_format_offset(){
        return mountain::get_format_offsets(&VertexWithColor::pos, &VertexWithColor::color);
    }
};

mountain::buffer::vertex create_quad_vertex_buffer(mountain::Context const& context);
#endif //MOUNTAIN_API_INIT_H
