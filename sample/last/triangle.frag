#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 frag_tex_coords;
layout(location = 0) out vec4 outColor;

layout(push_constant) uniform pushConstants {
    layout(offset=64) float color;
} u_push;

layout(set = 1, binding = 0) uniform buf{
    float color;
}ubo_color;
layout(set = 0, binding = 1) uniform sampler2D texSampler;

void main() {
    outColor = vec4(ubo_color.color*fragColor*u_push.color, 1.0);
    outColor = texture(texSampler, frag_tex_coords);
}