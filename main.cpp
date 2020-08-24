#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
//#include <cmath>
//#include <glm/glm.hpp>
#include "shader.hpp"
#include "stb_image.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

int main() {
    // Configure GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create the window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialise GLAD." << std::endl;
        return -1;
    }

    // Create shader program
    Shader ourShader("vertex.glsl", "fragment.glsl");

    // Push vertices into VBO
    float vertices[] = {
        // Positions          // Colours (unused)  // Texture co-ords
         0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, // Top right
         0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f, // Bottom right
        -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f, // Bottom left
        -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f, // Top left
    };

    unsigned int indices[] = {
        0, 2, 1,
        0, 2, 3
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // A VBO is an array of vertices for a geometry like a cube
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    // Colour
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Remove the VBO/VAO so they aren't overwritten
    glBindVertexArray(0);


    // Allocate glTexture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Parameterise glTexture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrap in s (across)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrap in t (down)

    // Load texture into memory and generate
    int width, height, numChannels;
    unsigned char* data = stbi_load("textures/container.jpg", &width, &height, &numChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data); // Free no longer needed memory

    // Update, render loop
    while(!glfwWindowShouldClose(window)) {
        // Handle input
        processInput(window);

        // Update program state

        // Draw to secondary buffer
        glClearColor(0.39f, 0.58f, 0.92f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw tri
        ourShader.use(); // Activate shader!
//        ourShader.setFloat("floatName", 1.0f);

        // Render the triangle
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Check for glfw events
        glfwPollEvents();

        // Swap draw buffers, i.e. display new image
        glfwSwapBuffers(window); // Double buffering, TODO: lookup swap-chain/triple-buffering
    }
//
    // De-allocate resources, done on exit anyway, but still
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    ourShader.destroy();

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); // Doesn't necessarily have to match the window size
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}
