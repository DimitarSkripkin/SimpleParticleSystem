#pragma once

#include <vector>
#include <map>

#include <glm/glm.hpp>

#include "Sprite.h"
#include "OpenGLWrapper/VAO.h"
#include "OpenGLWrapper/Texture.h"

struct SpriteVertex {
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec4 color;
};

struct DrawBatch2D {
    VAO vao;
    BufferGPU vertexBuffer;
    Texture* texture;
    std::vector<SpriteVertex> vertices;
};

struct DrawQuad {
    glm::vec2 size;
    glm::vec4 color;
};

class BatchRenderer;

class BatchRecorder {
    friend BatchRenderer;
public:
    ~BatchRecorder();

    void Add(const DrawQuad & drawQuad, glm::vec3 position, float rotation, glm::vec2 scale);
    void Add(const DrawQuad & drawQuad, float x, float y, float z, float rot = 0.0f, float scaleX = 1, float scaleY = 1);
    void Add(const DrawQuad & drawQuad, const glm::mat4 & mat);

    void Add(const Sprite & sprite, glm::vec3 position, float rotation, glm::vec2 scale);
    void Add(const Sprite & sprite, float x, float y, float z, float rot = 0.0f, float scaleX = 1, float scaleY = 1);
    void Add(const Sprite & sprite, const glm::mat4 & mat);

    void FinishRecording();
    void Clear();

private:
    std::map<Texture*, DrawBatch2D*> subBatches;
};
