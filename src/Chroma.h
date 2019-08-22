#pragma once

#include <chroma/main/Application.h>
#include <chroma/main/AssetImporter.h>
#include <chroma/main/Log.h>
#include <chroma/main/TimeStep.h>

#include <chroma/geometry/Mesh.h>

#include <chroma/renderer/Buffer.h>
#include <chroma/renderer/Camera.h>
#include <chroma/renderer/Layer.h>
#include <chroma/renderer/LayerStack.h>
#include <chroma/renderer/RenderContext.h>
#include <chroma/renderer/Scene.h>
#include <chroma/renderer/SceneObject.h>
#include <chroma/renderer/Shader.h>
#include <chroma/renderer/Texture.h>

#include <chroma/events/ApplicationEvent.h>
#include <chroma/events/Event.h>
#include <chroma/events/KeyEvent.h>
#include <chroma/events/MouseEvent.h>

#include <chroma/openGL/OpenGLBuffer.h>
#include <chroma/openGL/OpenGLContext.h>
#include <chroma/openGL/OpenGLVertexArrayObject.h>

#include <chroma/window/Window.h>

//-----------------Entry-Point--------------------
#include <chroma/main/main.h>