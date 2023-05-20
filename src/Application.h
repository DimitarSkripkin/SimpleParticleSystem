#pragma once

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
    bool shouldQuit = false;
};
