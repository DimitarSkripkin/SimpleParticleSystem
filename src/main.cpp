
#include <stdio.h>
#include <cstring>
#include <chrono>
#include <thread>
// #include <chrono>

#include <imgui.h>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GL/gl3w.h> // Initialize with gl3wInit()
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "Application.h"

static void GLFWErrorCallback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else {
        // probably something like
        // applicationPtr.UpdateInput(...event...);
    }
}

int main(int argc, const char * argv[]) {
    glfwSetErrorCallback(GLFWErrorCallback);

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    // Decide GL+GLSL versions
    // GL 3.3 + GLSL 330
    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    glfwWindowHint(GLFW_MAXIMIZED, 1);

    GLFWwindow *window = 0 ?
        glfwCreateWindow(mode->width, mode->height, "ParticleSystem", monitor, nullptr)
        : glfwCreateWindow(1280, 720, "ParticleSystem", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

    bool keyData[256];
    std::memset(&keyData, 0, sizeof(keyData));
    glfwSetWindowUserPointer(window, &keyData);
    glfwSetKeyCallback(window, KeyCallback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Initialize OpenGL loader
    bool err = gl3wInit() != 0;
    if (err) {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    {
        Application app;
        HWND hwnd = glfwGetWin32Window(window);
        app.Init(window, (void*)hwnd, glsl_version);

        // Main loop
        bool done = false;
        using namespace std::chrono_literals;
        std::chrono::high_resolution_clock timer;
        auto lastTime = timer.now();

        while (!done && !glfwWindowShouldClose(window)) {
            glfwPollEvents();

            auto currentTime = timer.now();
            float deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count() / 1000.0f;
            app.Update(deltaTime);
            lastTime = currentTime;

            app.Draw();

            glfwSwapBuffers(window);

            done |= app.ShouldQuit();
            // Not an actual game I don't need my laptop flying across the room...
            std::this_thread::sleep_for(5ms);
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
