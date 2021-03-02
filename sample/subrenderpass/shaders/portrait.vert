#version 450
#extension GL_ARB_separate_shader_objects : enable
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 tex_coords;

layout(location = 1) out vec2 frag_tex_coord;

void main() {

    gl_Position =   vec4(pos, 0.5, 1.0);
    frag_tex_coord = tex_coords;
}