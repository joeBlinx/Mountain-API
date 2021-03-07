#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 out_color;
layout(location = 0) in vec2 uv;

layout(set = 0, binding = 0) uniform sampler2D tex_sampler;
void main() {

    out_color = texture(tex_sampler, uv);
}