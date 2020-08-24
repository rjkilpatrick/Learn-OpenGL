#version 330 core
in vec3 ourColour; // Input variable from vertex shader
out vec4 FragColour;

void main() {
   FragColour = vec4(ourColour, 1.0);
}
