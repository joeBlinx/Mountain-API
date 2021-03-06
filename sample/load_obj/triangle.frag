#version 450
#extension GL_ARB_separate_shader_objects : enable


layout(location = 1) in vec2 frag_tex_coords;


layout(location = 0) out vec4 outColor;
layout(set = 0, binding = 1) uniform sampler2D texSampler;

void main() {
    outColor = texture(texSampler, frag_tex_coords);
}