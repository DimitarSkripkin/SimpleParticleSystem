#pragma once

#include "./Shader.h"
#include <glm/glm.hpp>

class ShaderProgram {
public:
    ShaderProgram();
    ShaderProgram(const ShaderProgram &other) = default;
    ~ShaderProgram();

    void Bind() const;

    void Unbind() const;

    uint32_t GetId() const;

    int32_t GetUniformLocation(const char * uniformName);
    int32_t GetUniformBlockIndex(const char * uniformName);
    int32_t GetUniformBlockiv(int32_t uniformBlockIndex);

    int32_t GetAttributeLocation(const char * attributeName);

    void SetUniformBlockBinding(int32_t uniformBlockIndex, uint32_t uniformBlockBinding);

    void SetInt(int32_t uniformLocation, int value);
    void SetFloat(int32_t uniformLocation, float value);

    void SetVec2(int32_t uniformLocation, float x, float y);
    void SetVec3(int32_t uniformLocation, float x, float y, float z);
    void SetVec3Array(int32_t uniformLocation, float *array, int32_t count);
    void SetVec4(int32_t uniformLocation, float x, float y, float z, float w);

    void SetMat4(int32_t uniformLocation, const glm::mat4 & mat);

    void BindFragDataLocation(const char * name, uint32_t colorNumber = 0);

    void AttachShader( const Shader &shader );

    void Link();

    void Create();

    void Destroy();

private:
    uint32_t programId;
};
