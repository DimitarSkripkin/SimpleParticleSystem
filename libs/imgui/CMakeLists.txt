# CMakeList.txt : CMake project for ExternalLibraries, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

project(ImGui VERSION 1.0.0)

add_library(ImGui INTERFACE)

target_sources(ImGui INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui-repo/imgui.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui-repo/imgui_draw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui-repo/imgui_widgets.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui-repo/imgui_tables.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui-repo/imgui_demo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui-repo/backends/imgui_impl_glfw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui-repo/backends/imgui_impl_opengl3.cpp"
)

target_compile_definitions(ImGui INTERFACE IMGUI_DISABLE_INCLUDE_IMCONFIG_H)

# OpenGL
find_package(OpenGL REQUIRED)

if(NOT ${OPENGL_FOUND})
    message("OPENGL not found")
endif()

target_include_directories(ImGui INTERFACE
    "${OPENGL_INCLUDE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui-repo/examples/libs/gl3w"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui-repo"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui-repo/backends"
)

target_link_libraries(ImGui INTERFACE
    ${OPENGL_LIBRARIES}
)
