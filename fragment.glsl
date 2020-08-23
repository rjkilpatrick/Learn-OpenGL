#version 330 core
out vec4 FragColour;
in vec3 ourColour; // Input variable from vertex shader

void main() {
   FragColour = vec4(ourColour, 1.0);
}
