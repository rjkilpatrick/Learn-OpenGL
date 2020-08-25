#version 330 core
out vec4 FragColour;

in vec3 ourColour; // Input variable from vertex shader
in vec2 UV;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    FragColour = mix(texture(texture1, UV), texture(texture2, vec2(UV.x, -UV.y)), 0.2);
}
