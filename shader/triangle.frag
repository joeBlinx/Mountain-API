#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragColor;

layout(location = 0) out vec4 outColor;

layout(push_constant) uniform pushConstants {
    layout(offset=8) float test1;
} u_push;
void main() {
    outColor = vec4(fragColor*vec3(u_push.test1), 1.0);
}