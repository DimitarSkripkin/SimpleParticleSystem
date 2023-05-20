# CMakeList.txt : CMake project for ExternalLibraries, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

project(gl3w VERSION 1.0.0)

add_library(gl3w INTERFACE)

target_sources(gl3w INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/gl3w.c"
)

# OpenGL
find_package(OpenGL REQUIRED)

if(NOT ${OPENGL_FOUND})
    message("OPENGL not found")
endif()

target_include_directories(gl3w INTERFACE
    "${OPENGL_INCLUDE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(gl3w INTERFACE
    ${OPENGL_LIBRARIES}
)
