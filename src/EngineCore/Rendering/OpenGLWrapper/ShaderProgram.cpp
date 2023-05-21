#include <cstring>
#include <iostream>

#include <glm/glm.hpp>

#include "ShaderProgram.h"

// TODO: check why the function was static
void ValidateProgram(GLuint program) {
    const uint16_t BUFFER_SIZE = 512;
    char buffer[ BUFFER_SIZE ];
    memset(buffer, 0, BUFFER_SIZE);
    GLsizei length = 0;

    glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer);
    if (length > 0) {
        std::cerr << "Program " << program << " link error: " << buffer << std::endl;
    }

    glValidateProgram(program);
    GLint status;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
    if (status == GL_FALSE) {
        std::cerr << "Error validating shader " << program << std::endl;
    }
}

ShaderProgram::ShaderProgram()
    : programId(0)
{}

ShaderProgram::~ShaderProgram() {
    Destroy();
}

void ShaderProgram::Bind() const {
    glUseProgram(programId);
}

void ShaderProgram::Unbind() const {
    glUseProgram(0);
}

uint32_t ShaderProgram::GetId() const {
    return programId;
}

int32_t ShaderProgram::GetUniformLocation(const char * uniformName) {
    return glGetUniformLocation(programId, uniformName);
}

int32_t ShaderProgram::GetUniformBlockIndex(const char * uniformName) {
    return glGetUniformBlockIndex(programId, uniformName);
}

int32_t ShaderProgram::GetUniformBlockiv(int32_t uniformBlockIndex) {
    int32_t blockSize = 0;
    glGetActiveUniformBlockiv(programId, uniformBlockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
    return blockSize;
}

int32_t ShaderProgram::GetAttributeLocation(const char * attributeName) {
    return glGetAttribLocation(programId, attributeName);
}

void ShaderProgram::SetUniformBlockBinding(int32_t uniformBlockIndex, uint32_t uniformBlockBinding) {
    glUniformBlockBinding(programId, uniformBlockIndex, uniformBlockBinding);
}

void ShaderProgram::SetInt(int32_t uniformLocation, int value) {
    glUniform1i(uniformLocation, value);
}
void ShaderProgram::SetFloat(int32_t uniformLocation, float value) {
    glUniform1f(uniformLocation, value);
}

void ShaderProgram::SetVec2(int32_t uniformLocation, float x, float y) {
    glUniform2f(uniformLocation, x, y);
}
void ShaderProgram::SetVec3(int32_t uniformLocation, float x, float y, float z) {
    glUniform3f(uniformLocation, x, y, z);
}
void ShaderProgram::SetVec3Array(int32_t uniformLocation, float *array, int32_t count) {
    glUniform3fv(uniformLocation, count, array);
}
void ShaderProgram::SetVec4(int32_t uniformLocation, float x, float y, float z, float w) {
    glUniform4f(uniformLocation, x, y, z, w);
}

void ShaderProgram::SetMat4(int32_t uniformLocation, const glm::mat4 & matrix) {
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::BindFragDataLocation(const char * name, uint32_t colorNumber) {
    glBindFragDataLocation(programId, colorNumber, name);
}

void ShaderProgram::AttachShader(const Shader & shader) {
    glAttachShader(programId, shader.GetId());
}

void ShaderProgram::Link() {
    glLinkProgram(programId);
    ValidateProgram(programId);
}

void ShaderProgram::Create() {
    programId = glCreateProgram();
}

void ShaderProgram::Destroy() {
    glDeleteProgram(programId);
}
