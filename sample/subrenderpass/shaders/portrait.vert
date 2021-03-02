#version 450
#extension GL_ARB_separate_shader_objects : enable
layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 color;

layout(location = 1) out vec4 out_color;

layout(push_constant) uniform pushConstants {
    mat4 model;
} model;

void main() {

    gl_Position = model.model*vec4(pos, 1.0);
    out_color = color;
}