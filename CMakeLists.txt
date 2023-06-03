cmake_minimum_required(VERSION 3.0.0)
project(ParticleSystem VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

add_subdirectory("libs/gl3w")

add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_subdirectory("libs/imgui")

# add_definitions(-DGLM_FORCE_XYZW_ONLY)
add_subdirectory("libs/glm")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory("libs/glfw")

add_executable(${PROJECT_NAME}
    "src/main.cpp"
    "src/Application.cpp"

    "src/EngineCore/Core/AssetManager.cpp"

    "src/EngineCore/FileLoaders/RawImage.cpp"

    "src/EngineCore/Rendering/OpenGLWrapper/BufferGPU.cpp"
    "src/EngineCore/Rendering/OpenGLWrapper/DebugGL.cpp"
    "src/EngineCore/Rendering/OpenGLWrapper/Shader.cpp"
    "src/EngineCore/Rendering/OpenGLWrapper/ShaderProgram.cpp"
    "src/EngineCore/Rendering/OpenGLWrapper/Texture.cpp"
    "src/EngineCore/Rendering/OpenGLWrapper/VAO.cpp"

    "src/EngineCore/Rendering/BatchRecorder.cpp"
    "src/EngineCore/Rendering/BatchRenderer.cpp"

    "src/EngineCore/Systems/ParticleSystem.cpp"

    "src/EngineCore/Utils/FileUtils.cpp"
    "src/EngineCore/Utils/Math.cpp"
)

# OpenGL
find_package(OpenGL REQUIRED)

if(NOT ${OPENGL_FOUND})
    message("OPENGL not found")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    "${OPENGL_INCLUDE_DIR}"
    # "libs"
    "libs/HeadersOnly"
    "src"
)

target_link_libraries(${PROJECT_NAME}
    gl3w
    ImGui
    ${OPENGL_LIBRARIES}
    glfw
    glm
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets")
