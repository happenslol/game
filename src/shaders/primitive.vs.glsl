#version 330 core

layout (location = 0) in vec2 a_position;
layout (location = 1) in vec3 a_color;

out vec3 color;

uniform mat4 projection;

void main() {
    gl_Position = projection * vec4(a_position, 0.0, 1.0);
    color = a_color;
}

