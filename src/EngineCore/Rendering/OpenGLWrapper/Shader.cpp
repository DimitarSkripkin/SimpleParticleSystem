#include <cstring>
#include <string>
#include <fstream>
#include <iostream>

#include "EngineCore/Utils/FileUtils.h"

#include "Shader.h"

void ValidateShader(GLuint shaderId, const char *file = 0) {
    const unsigned int BUFFER_SIZE = 512;
    char buffer[ BUFFER_SIZE ];
    memset(buffer, 0, BUFFER_SIZE);
    GLsizei length = 0;

    glGetShaderInfoLog(shaderId, BUFFER_SIZE, &length, buffer);
    if (length > 0) {
        std::cerr << "Shader " << shaderId << " (" << (file ? file : "") << ") compile error: " << buffer << std::endl;
    }
}

Shader::Shader()
    : shaderId(0)
{}

Shader::~Shader() {
    Delete();
}

uint32_t Shader::GetId() const {
    return shaderId;
}

ShaderType Shader::GetType() const {
    return shaderType;
}

int Shader::InitSource(const char *shaderSource, ShaderType shaderType) {
    if (!shaderSource) {
        std::cerr << "Empty shader source" << std::endl;
        return -1;
    }

    shaderId = glCreateShader(static_cast<uint16_t>(shaderType));
    glShaderSource(shaderId, 1, &shaderSource, 0);
    glCompileShader(shaderId);

    ValidateShader(shaderId, shaderSource);

    shaderType = shaderType;
    return 0;
}

// should throw
int Shader::InitFile(const char *fileName, ShaderType shaderType) {
    std::string shaderSource = EngineCore::Utils::FileUtils::LoadTextFile(fileName);
    if (!shaderSource.size()) {
        std::cerr << "Empty shader file" << std::endl;
        return -2;
    }

    int res = InitSource(shaderSource.c_str(), shaderType);
    return res;
}

void Shader::Delete() {
    if (shaderId) {
        glDeleteShader(shaderId);
        shaderId = 0;
    }
}
