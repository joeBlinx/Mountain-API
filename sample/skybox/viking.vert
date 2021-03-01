#version 450
#extension GL_ARB_separate_shader_objects : enable
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex_coords;

layout(location = 1) out vec2 frag_tex_coord;

layout(set = 0, binding = 2) uniform uniform_buffer{
    mat4 view;
    mat4 proj;
}ubo;

void main() {
    gl_Position = ubo.proj * ubo.view * model.model *vec4(pos, 1.0);
    frag_tex_coord = tex_coords;
}