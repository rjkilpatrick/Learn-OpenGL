#version 330 core
out vec4 FragColour;

in vec3 ourColour; // Input variable from vertex shader
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main() {
   FragColour = texture(ourTexture, TexCoord);
}
