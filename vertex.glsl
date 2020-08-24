#version 330 core
layout (location = 0) in vec3 aPos; // Position variable has attribute position 0
layout (location = 1) in vec3 aColour; // Colour variable has attribute position 1

out vec3 ourColour; // Output for frag shader

void main() {
    gl_Position = vec4(aPos, 1.0); // vec3 -> vec4 just like css with rgba()
    ourColour = aPos;
}
