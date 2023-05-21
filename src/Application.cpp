#include "Application.h"

#include <GL/gl3w.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "EngineCore/Core/AssetManager.h"
#include "EngineCore/Rendering/OpenGLWrapper/DebugGL.h"

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
}

void Application::Update(float deltaTime) {
    lastDeltaTime = deltaTime;
}

void Application::Draw() {
    CheckForGLErrors();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static glm::vec3 color(0.45f);
    glClearColor(color.x, color.y, color.z, 1.00f);

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
