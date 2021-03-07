//
// Created by stiven_perso on 3/7/21.
//

#include "init.h"
#include "mountain/context.h"
#include "glm/glm.hpp"
#include <array>
mountain::buffer::vertex create_quad_buffers_with_uv(mountain::Context const& context){
    struct Vertex{
        glm::vec2 pos; // location 0
        glm::vec2 uv; // location 1
        static auto get_description() {
            return mountain::get_format_offsets(&Vertex::pos, &Vertex::uv);
        }
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
            Vertex{{-1.f, -1.f}, {0.0f, 0.f}}, // 0
            Vertex{{1.f, -1.f}, {1.0f, 0.f}},// 1
            Vertex{{-1.f, 1.f}, {0.0f, 1.f}},// 2
            Vertex{{1.f, 1.f}, {1.0f, 1.f}} // 3
    };
    std::array<uint32_t, 6> constexpr indices{2, 1, 0, 1, 2, 3};
    std::vector<mountain::buffer::vertex> buffers;

    return mountain::buffer::vertex{context,
                                    mountain::buffer::vertex_description(0,
                                                                         0,
                                                                         Vertex::get_description()),
                                    vertices,
                                    indices};
}

mountain::buffer::vertex create_triangle_buffer_with_color(mountain::Context const& context){
    struct Vertex{
        glm::vec2 pos; // location 0
        glm::vec3 color; // location 1
        static auto get_description() {
            return mountain::get_format_offsets(&Vertex::pos, &Vertex::color);
        }
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
    return mountain::buffer::vertex{context,
                                    mountain::buffer::vertex_description(0,
                                                                         0,
                                                                         Vertex::get_description()),
                                    vertices,
                                    indices};
}