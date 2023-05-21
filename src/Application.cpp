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
#include "EngineCore/Rendering/Material.h"
#include "EngineCore/Rendering/OpenGLWrapper/DebugGL.h"
#include "EngineCore/Rendering/OpenGLWrapper/BufferGPU.h"
#include "EngineCore/Rendering/OpenGLWrapper/VAO.h"

struct SpriteVertex {
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec4 color;
};

struct TestRenderData {
    VAO vao;
    BufferGPU vertexBuffer;
    std::vector<SpriteVertex> vertices;
};

static Ref<TestRenderData> trd;
static Ref<SpriteMaterial> spriteMaterial;

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
    particleTexture = assetManager.LoadCachedImageFile("assets/textures/fire_01.png");

    trd = CreateRef<TestRenderData>();
    trd->vao.Generate();
    trd->vao.Bind();

    trd->vertexBuffer.GenerateBuffer(GL_ARRAY_BUFFER);

    glm::vec2 quadSize(250.0f);
    SpriteVertex vecBottomLeft { { 0, 0, 0 }, { 0.0f, 1.0f }, glm::vec4(1.0) };
    SpriteVertex vecBottomRight { { quadSize.x, 0, 0 }, { 1.0f, 1.0f }, glm::vec4(1.0) };
    SpriteVertex vecTopLeft { { 0, quadSize.y, 0 }, { 0.0f, 0.0f }, glm::vec4(1.0) };
    SpriteVertex vecTopRight { { quadSize.x, quadSize.y, 0 }, { 1.0f, 0.0f }, glm::vec4(1.0) };

    trd->vertices.push_back(vecBottomLeft);
    trd->vertices.push_back(vecBottomRight);
    trd->vertices.push_back(vecTopLeft);
    // second triangle
    trd->vertices.push_back(vecTopLeft);
    trd->vertices.push_back(vecBottomRight);
    trd->vertices.push_back(vecTopRight);

    trd->vertexBuffer.BindData(trd->vertices.data(), sizeof(SpriteVertex) * trd->vertices.size(), GL_DYNAMIC_DRAW);

    // vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (GLvoid*)offsetof(SpriteVertex, position));

    // uv
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (GLvoid*)offsetof(SpriteVertex, uv));

    // color
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (GLvoid*)offsetof(SpriteVertex, color));

    spriteMaterial = CreateRef<SpriteMaterial>();
    spriteMaterial->Bind();
    spriteMaterial->UpdateTexture(particleTexture.get());

    int displayWidth, displayHeight;
    glfwGetFramebufferSize(window, &displayWidth, &displayHeight);
    auto orthographicMatrix = glm::ortho(0.0f, (float)displayWidth, 0.0f, (float)displayHeight);
    spriteMaterial->UpdateProjection(orthographicMatrix);
    spriteMaterial->Unbind();
}

void Application::Update(float deltaTime) {
    lastDeltaTime = deltaTime;
    totalWorkingTime += deltaTime;

    spriteMaterial->Bind();
    glm::mat4 modelViewMatrix(1.0f);
    modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(250.0f, 250.0f, 0.0f));
    float movementSpeed = 10.0f;
    modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(movementSpeed * totalWorkingTime, movementSpeed * totalWorkingTime, 0.0f));
    spriteMaterial->UpdateModelView(modelViewMatrix);

    totalWorkingTime += deltaTime;
    spriteMaterial->Unbind();
}

void Application::Draw() {
    CheckForGLErrors();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static glm::vec3 color(0.45f);
    glClearColor(color.x, color.y, color.z, 1.00f);

    spriteMaterial->Bind();
    trd->vao.Bind();

    glDrawArrays(GL_TRIANGLES, 0, static_cast<uint32_t>(trd->vertices.size()));

    trd->vao.Unbind();
    spriteMaterial->Unbind();

    // TEMP will be moved
    ImGuiIO &io = ImGui::GetIO();

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
