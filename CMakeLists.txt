
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
     src/chroma/main/Application.h
     src/chroma/main/Application.cpp
     src/chroma/main/AssetImporter.cpp
     src/chroma/main/AssetImporter.h
     src/chroma/main/Input.h
     src/chroma/main/KeyCodes.h
     src/chroma/main/Log.h
     src/chroma/main/Log.cpp
     src/chroma/main/entry.cpp
     src/chroma/main/TimeStep.h
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
    src/thirdparty/tinyobjloader/tiny_obj_loader.h
    src/thirdparty/OBJ_loader/OBJ_Loader.h
    src/thirdparty/stb_image/stb_image.h
)

source_group ("thirdparty\\" FILES
    ${thirdparty_sources}
)

set (opengl_sources
    src/chroma/openGL/OpenGLContext.h
    src/chroma/openGL/OpenGLContext.cpp
    src/chroma/openGL/openGLBuffer.h
    src/chroma/openGL/openGLBuffer.cpp
    src/chroma/openGL/openGLVertexArrayObject.h
    src/chroma/openGL/openGLVertexArrayObject.cpp
)

source_group ("opengl\\" FILES
    ${opengl_sources}
)

set (event_sources
    src/chroma/events/Event.h
    src/chroma/events/KeyEvent.h
    src/chroma/events/ApplicationEvent.h
    src/chroma/events/MouseEvent.h
)

source_group ("events\\" FILES
    ${event_sources}
)

set(window_sources
    src/chroma/window/Window.h
    src/chroma/window/Window.cpp
    src/chroma/window/WindowsInput.h
    src/chroma/window/WindowsInput.cpp
    )

source_group ("window\\" FILES
    ${window_sources}
)

set(renderer_sources
    src/chroma/renderer/RenderContext.h
    src/chroma/renderer/Layer.h
    src/chroma/renderer/Layer.cpp
    src/chroma/renderer/Shader.h
    src/chroma/renderer/Shader.cpp
    src/chroma/renderer/Buffer.h
    src/chroma/renderer/Camera.h
    src/chroma/renderer/Camera.cpp
    src/chroma/renderer/Texture.h
    src/chroma/renderer/Texture.cpp
    src/chroma/renderer/Light.h
    src/chroma/renderer/Scene.h
    src/chroma/renderer/Scene.cpp
    src/chroma/renderer/SceneObject.h
    src/chroma/renderer/SceneObject.cpp
    src/chroma/renderer/LayerStack.h
    src/chroma/renderer/LayerStack.cpp
)

source_group ("renderer\\" FILES
    ${renderer_sources}
)

set(geometry_sources
    src/chroma/geometry/Mesh.h
    src/chroma/geometry/Mesh.cpp
)

source_group ("geometry\\" FILES
    ${geometry_sources}
)

#not ideal to include like this but make do...
set(sandbox_sources
    sandbox/src/Sandbox.cpp
)

source_group ("sandbox\\" FILES
    ${sandbox_sources}
)

add_executable (chroma
    ${main_sources}
    ${opengl_sources}
    ${renderer_sources}
    ${window_sources}
    ${thirdparty_sources}
    ${event_sources}
    ${geometry_sources}
    ${sandbox_sources}
    src/Chroma.h
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