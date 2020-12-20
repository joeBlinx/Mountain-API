#version 450
#extension GL_ARB_separate_shader_objects : enable
layout(location = 0) in vec2 pos;
layout(location = 1) in vec3 colors;
layout(location = 0) out vec3 fragColor;
layout(push_constant) uniform pushConstants {
   mat4 model;
} model;
layout(binding = 0) uniform uniform_buffer{
    mat4 view;
    mat4 proj;
}ubo;

void main() {
    gl_Position = ubo.proj * ubo.view * model.model *vec4(pos, 0.0, 1.0);
    fragColor = colors;
}