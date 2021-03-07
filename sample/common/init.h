//
// Created by stiven_perso on 3/7/21.
//

#ifndef MOUNTAIN_API_INIT_H
#define MOUNTAIN_API_INIT_H
#include "mountain/vertex.h"
namespace mountain{
    struct Context;
}
mountain::buffer::vertex create_quad_buffers_with_uv(mountain::Context const& context);
mountain::buffer::vertex create_triangle_buffer_with_color(mountain::Context const& context);
#endif //MOUNTAIN_API_INIT_H
