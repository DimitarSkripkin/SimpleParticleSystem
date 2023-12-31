#pragma once

#include "EngineCore/Systems/ParticleSystem.h"
#include "EngineCore/Rendering/OpenGLWrapper/Texture.h"
#include "EngineCore/Rendering/BatchRenderer.h"

struct GLFWwindow;

class Application {
public:

    void Init(GLFWwindow *window, void *mainWindowHandler, const char *glsl_version);

    void Update(float deltaTime);

    void Draw();

    bool ShouldQuit() {
        return shouldQuit;
    }

private:
    GLFWwindow *window;
    void *mainWindowHandler;

    float lastDeltaTime = 0.0f;
    float totalWorkingTime = 0.0f;
    bool shouldQuit = false;

    Ref<SpriteMaterial> spriteMaterial;
    Ref<Texture> particleTexture;

    BatchRecorder batchRecorder;
    BatchRenderer batchRenderer;

    EngineCore::Systems::ParticleSystem particleSystem;

    void DrawUI();
};
