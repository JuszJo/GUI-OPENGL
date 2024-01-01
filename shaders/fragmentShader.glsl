#version 330 core

in vec3 fragColor;
in vec2 textureCoord;

uniform vec3 color;
uniform sampler2D myTexture;

out vec4 FragColor;

void main() {
    // FragColor = texture(myTexture, textureCoord) * vec4(fragColor * color, 1.0);
    FragColor = texture(myTexture, textureCoord);
    // FragColor = vec4(color, 1.0);
}