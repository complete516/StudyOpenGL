#version 330 core
out vec4 FragColor;

uniform sampler2D boxSampler;

in vec2 TexCoords;

void main() {
    FragColor = texture(boxSampler,TexCoords);
}