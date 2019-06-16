
cmake_minimum_required(VERSION 2.6)

project(chroma)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_CONFIGURATION_TYPES Debug Release)

# The following folder will be included
include_directories(src)

set (main_sources
     src/chroma/main/main.cpp
     src/chroma/main/Log.h
     src/chroma/main/Log.cpp
)

source_group ("main\\" FILES
    ${main_sources}
)

#include glfw
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
add_subdirectory(src/thirdparty/glfw-3.3)

#include spdlog
add_subdirectory(src/thirdparty/spdlog-1.3.1)

set (thirdparty_sources
    #src/thirdparty/gl3w/include/GL/gl3w.h
    #src/thirdparty/gl3w/include/GL/glcorearb.h
    #src/thirdparty/gl3w/include/KHR/khrplatform.h
    #src/thirdparty/gl3w/src/gl3w.c
    src/thirdparty/glad/include/glad/glad.h
    src/thirdparty/glad/include/KHR/khrplatform.h
    src/thirdparty/glad/src/glad.c
    src/thirdparty/imgui/imconfig.h
    src/thirdparty/imgui/imgui.cpp
    src/thirdparty/imgui/imgui.h
    src/thirdparty/imgui/imgui_demo.cpp
    src/thirdparty/imgui/imgui_draw.cpp
    src/thirdparty/imgui/imgui_internal.h
    src/thirdparty/imgui/imgui_widgets.cpp
)

source_group ("thirdparty\\" FILES
    ${thirdparty_sources}
)

set (opengl_sources
    src/chroma/openGL/OpenGLContext.h
    src/chroma/openGL/OpenGLContext.cpp
)

source_group ("opengl\\" FILES
    ${opengl_sources}
)

set ( event_sources
    src/chroma/events/Event.h
    src/chroma/events/KeyEvent.h
    src/chroma/events/ApplicationEvent.h
)

source_group ("events\\" FILES
    ${event_sources}
)

set(window_sources
    src/chroma/window/Window.h
    src/chroma/window/Window.cpp)

source_group ("window\\" FILES
    ${window_sources}
)

set(renderer_sources
    src/chroma/renderer/RenderContext.h
)

source_group ("renderer\\" FILES
    ${renderer_sources}
)

add_executable (chroma
    ${main_sources}
    ${opengl_sources}
    ${renderer_sources}
    ${window_sources}
    ${thirdparty_sources}
    ${event_sources}
)

# Find and link to OpenGL
include(FindOpenGL)
target_link_libraries(chroma ${OPENGL_gl_LIBRARY})

# Link to glfw
target_link_libraries(chroma glfw)

#Link spdlog
target_link_libraries(chroma spdlog)

#Windows
add_definitions(-DNOC_FILE_DIALOG_IMPLEMENTATION)
add_definitions(-DNOC_FILE_DIALOG_WIN32)
set_target_properties(
   chroma
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

set_target_properties(
    chroma
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY  "${CMAKE_SOURCE_DIR}/bin/$(Configuration)")

# Create logs directory
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/logs")