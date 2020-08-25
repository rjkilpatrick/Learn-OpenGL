#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    public:
        unsigned int program; // ID of program

        Shader(const char* vertexPath, const char* fragmentPath);

        void use(); // Use / Activate shader program

        // Uniform manipulation
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;

        void destroy();

    private:
        // std::string load_file(const char* filePath) const;
        std::string load_file(const char* filePath) const;
};

#endif // SHADER_H
