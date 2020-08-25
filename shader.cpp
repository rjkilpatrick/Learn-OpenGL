#include "shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    // Retrieve vertex & fragment shaders from given paths
    std::string vertexCode = load_file(vertexPath);
    const char* vShaderCode = vertexCode.c_str();

    std::string fragmentCode = load_file(fragmentPath);
    const char* fShaderCode = fragmentCode.c_str();

    // Compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // Vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER:VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Shader program
    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    // Print linking errors
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Delete lone shaders as they're now useless
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}


std::string Shader::load_file(const char* filePath) const {
    // Retrieve vertex & fragment shaders from given paths
     std::string code;
    std::ifstream shaderFile;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // Open files
        shaderFile.open(filePath);
        std::stringstream shaderStream;

        // Read buffer into stream
        shaderStream << shaderFile.rdbuf();

        shaderFile.close();

        code = shaderStream.str();
    } catch (std::ifstream::failure &e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    return code;
}


void Shader::use() {
    glUseProgram(program);
}


void Shader::setBool(const std::string &name, bool value) const {
    // Gets uniform by name
    // Sets the uniform to value given

    glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}


void Shader::setInt(const std::string &name, int value) const {
    // Gets uniform by name
    // Sets the uniform to value given
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}


void Shader::setFloat(const std::string &name, float value) const {
    // Gets uniform by name
    // Sets float to the uniform to value given
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

void Shader::destroy() {
    glDeleteProgram(program);
}
