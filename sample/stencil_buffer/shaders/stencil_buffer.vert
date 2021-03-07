#version 450
#extension GL_ARB_separate_shader_objects : enable
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 uv;

layout(location = 0) out vec2 out_uv;
layout(push_constant) uniform pushConstants {
    mat4 model;
} model;

void main() {
    gl_Position = model.model*vec4(pos, 0.0, 1.0);
    out_uv = uv;
}