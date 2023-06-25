#include "Application.h"

#include <vector>

#include <GL/gl3w.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "EngineCore/Core/AssetManager.h"
#include "EngineCore/Rendering/OpenGLWrapper/DebugGL.h"
#include "EngineCore/Rendering/OpenGLWrapper/BufferGPU.h"
#include "EngineCore/Rendering/OpenGLWrapper/VAO.h"

// called on startup
void Application::Init(GLFWwindow *window, void *mainWindowHandler, const char *glsl_version) {
    this->mainWindowHandler = mainWindowHandler;
    EnableOpenGLDebugging();

    glClearDepth( 1.0f );
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    // glFrontFace(GL_CW);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    this->window = window;

    auto & assetManager = EngineCore::Core::AssetManager::Instance();
    // particleTexture = assetManager.LoadCachedImageFile("assets/textures/fire_01.png");
    particleTexture = assetManager.LoadCachedImageFile("assets/textures/smoke_01.png");

    spriteMaterial = CreateRef<SpriteMaterial>();
    spriteMaterial->Bind();
    spriteMaterial->UpdateTexture(particleTexture.get());

    int displayWidth, displayHeight;
    glfwGetFramebufferSize(window, &displayWidth, &displayHeight);

    auto orthographicMatrix = glm::ortho(0.0f, (float)displayWidth, 0.0f, (float)displayHeight);
    spriteMaterial->UpdateProjection(orthographicMatrix);
    spriteMaterial->UpdateModelView(glm::mat4(1.0f));

    spriteMaterial->Unbind();

    auto emitter = particleSystem.GetEmitter();
    emitter->particleProps.lifeTime = 5.0f;
    emitter->particleProps.initialPosition = glm::vec3(displayWidth / 2.0f, 250.0f, 0.0f);
    emitter->particleProps.initialVelocity = glm::vec3(50.0f, 50.0f, 0.0f);
    emitter->particleProps.initialSize = 50.0f;
    emitter->particleProps.endSize = 100.0f;
    emitter->particleProps.initialColor = glm::vec4(1.0f);
    emitter->particleProps.endColor = glm::vec4(0.0f);
    emitter->particlesPerSecond = 100.0f;
    emitter->spawnShape = EngineCore::Systems::SpawnShape::DIRECTION;
    emitter->directionSpread = 0.2f;

    auto particleSprite = CreateRef<Sprite>(particleTexture.get());
    emitter->particleProps.sprite = particleSprite;
}

void Application::Update(float deltaTime) {
    lastDeltaTime = deltaTime;
    totalWorkingTime += deltaTime;

    glm::mat4 modelViewMatrix(1.0f);
    modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(250.0f, 250.0f, 0.0f));
    float movementSpeed = 10.0f;
    modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(movementSpeed * totalWorkingTime, movementSpeed * totalWorkingTime, 0.0f));

    batchRecorder.Clear();
    // batchRecorder.Add(Sprite(0, 0, particleTexture->GetWidth(), particleTexture->GetHeight(), particleTexture.get()), modelViewMatrix);
    particleSystem.Update(deltaTime);
    particleSystem.AppendParticleData(batchRecorder);
    batchRecorder.FinishRecording();

    totalWorkingTime += deltaTime;
}

void Application::Draw() {
    CheckForGLErrors();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    spriteMaterial->Bind();
    batchRenderer.Draw(batchRecorder, *spriteMaterial);
    spriteMaterial->Unbind();

    DrawUI();
}

void Application::DrawUI() {
    static glm::vec3 color(0.7f);
    glClearColor(color.x, color.y, color.z, 1.00f);

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Color");

    ImGuiColorEditFlags flags = ImGuiColorEditFlags_None;
    ImGui::ColorEdit3("Background Color", glm::value_ptr(color), flags);

    intptr_t textureId = particleTexture->GetId();
    auto thumbnailSize = 256.0f;
    ImGui::Image(reinterpret_cast<ImTextureID>(textureId), { thumbnailSize, thumbnailSize });

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
