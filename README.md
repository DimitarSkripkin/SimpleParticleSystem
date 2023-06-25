# Particle System

Project developed for university course.

## Setup instructions

### Windows

1. Install Visual Studio 2022 (Community version can be used) with `Desktop development with C++` option selected.

2. Clone the repository using the following git command:
```
git clone --recurse-submodules https://github.com/DimitarSkripkin/SimpleParticleSystem.git
```

3. Right click on the cloned repository folder and click the option `Open with Visual Studio`.

4. Wait for Visual Studio to open and CMake configuration to finish.

5. Right click on `CMakeLists.txt` and choose the `Set as Startup Item`.

6. Hit `F5` to build and start the project.

## Used assets

https://opengameart.org/content/particle-pack-80-sprites

## Used Libraries

### GLM
Vector and Matrix structures

https://github.com/g-truc/glm

### gl3w
Simple OpenGL core profile loading

https://github.com/skaslev/gl3w

### ImGui
UI

https://github.com/ocornut/imgui/tree/docking

### GLFW
Creating window with OpenGL 3.3 context

https://github.com/glfw/glfw

### stb
stb_image - For loading images

https://github.com/nothings/stb/blob/master/stb_image.h
