#pragma once

#include <vector>
#include <string>
#include <array>
#include <iostream>

#include <glm/glm.hpp>

#include "EngineCore/Rendering/OpenGLWrapper/ShaderProgram.h"
#include "EngineCore/Rendering/OpenGLWrapper/Texture.h"

class Material {
public:
    Material() = default;
    virtual ~Material() = default;

    virtual void Bind() {}
    virtual void Unbind() {}
};

class SpriteMaterial
    : public Material
{
public:
    SpriteMaterial() {
        Init();
    }

    virtual void Bind() override {
        shaderProgram.Bind();
    }

    virtual void Unbind() override {
        shaderProgram.Unbind();
    }

    void UpdateTexture(Texture * texture) {
        texture->Bind();
    }

    void UpdateProjection(glm::mat4 projectionMatrix) {
        glUniformMatrix4fv(projectionMatrixId, 1, GL_FALSE, &projectionMatrix[0][0]);
    }

    void UpdateModelView(glm::mat4 modelViewMatrix) {
        glUniformMatrix4fv(modelViewMatrixId, 1, GL_FALSE, &modelViewMatrix[0][0]);
    }

private:
    ShaderProgram shaderProgram;

    GLint projectionMatrixId;
    GLint modelViewMatrixId;
    GLint albedoMapId;

    void Init() {
        shaderProgram.Create();

        Shader vertShader;
        vertShader.InitFile("assets/shaders/sprite.vert", ShaderType::VERTEX_SHADER);
        shaderProgram.AttachShader(vertShader);

        Shader fragShader;
        fragShader.InitFile("assets/shaders/sprite.frag", ShaderType::FRAGMENT_SHADER);
        shaderProgram.AttachShader(fragShader);

        shaderProgram.Link();
        shaderProgram.Bind();

        projectionMatrixId = shaderProgram.GetUniformLocation("projection");
        modelViewMatrixId = shaderProgram.GetUniformLocation("modelView");

        albedoMapId = shaderProgram.GetUniformLocation("albedoMap");

        shaderProgram.BindFragDataLocation("fragColor");
    }
};
