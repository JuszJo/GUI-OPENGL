#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
layout (location = 2) in vec2 tex;

uniform mat4 projection;

out vec3 fragColor;
out vec2 textureCoord;

void main() {
    gl_Position = projection * vec4(pos, 1.0);
    fragColor = col;
    textureCoord = tex;
}