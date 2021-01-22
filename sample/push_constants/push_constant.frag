#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 outColor;
layout(location = 0) in vec3 color;
layout(push_constant) uniform pushConstants {
    layout(offset=64) float color;
} u_push;

void main() {
    outColor = u_push.color*vec4(color, 1.0);
}