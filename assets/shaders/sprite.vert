#version 330 core

uniform mat4 modelView;
uniform mat4 projection;

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec4 color;


out VS_OUT {
    vec4 color;
    vec2 uv;
} vs_out;

void main() {
    vs_out.color = color;
    vs_out.uv = uv;
    gl_Position = projection * (modelView * vec4(vertex, 1.0));
    // gl_Position = vec4((projection * (modelView * vec4(vertex, 1.0))).xy, vertex.z, 1.0);
    // gl_Position = projection * vec4(vertex, 1.0);
}
