#pragma once

#include <thirdparty/glad/include/glad/glad.h>

#include "Application.h"

#include <chroma/main/Log.h>
#include <chroma/renderer/Shader.h>
#include <chroma/openGL/OpenGLBuffer.h>
#include <chroma/openGL/OpenGLVertexArrayObject.h>

#include <fstream>
#include <thirdparty/glm/glm/glm.hpp>
#include <thirdparty/glm//glm/gtc/matrix_transform.hpp>

namespace Chroma
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_instance = nullptr;

    Application::Application()
    {
        CH_ASSERT(!s_instance, "Application already running");

        Chroma::WindowProps props = Chroma::WindowProps();
        m_window = new Chroma::Window(props);
        m_window->SetEventCallback(BIND_EVENT_FN(OnEvent));

        m_running = true;
    }

    Application::~Application()
    {
    }

    void Chroma::Application::Run()
    {
        glClearColor(0.184f, 0.062f, 0.129f, 1.0f);
        // An array of 3 vectors which represents 3 vertices
        static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,  0.0f,  0.00f,
        1.0f, -1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
        0.0f,  1.0f, 0.0f, 0.0f,  0.0f,  1.0f,
        };


        //Vertex Array object
        OpenGLVertexArrayObject vao;
        //vertex buffer
        OpenGLVertexBuffer vertex_buffer((void*)&g_vertex_buffer_data, sizeof(g_vertex_buffer_data));

        //attributes vertex coords and colors
        VertexAttribute layout_attribute("vertex_coords", 0, ShaderDataType::Float3, GL_FALSE);
        VertexAttribute layout_attribute2("vertex_colors", 1, ShaderDataType::Float3, GL_FALSE);

        //Create Vertex Buffer Layout
        VertexBufferLayout vertex_buffer_layout;
        vertex_buffer_layout.PushAttribute(layout_attribute);
        vertex_buffer_layout.PushAttribute(layout_attribute2);

        //Give vertex buffer the layout
        vertex_buffer.SetBufferLayout(vertex_buffer_layout);
        vao.SetVertexBuffer(vertex_buffer);

        vertex_buffer.Unbind();//To prove VAO works

        // Create and compile our GLSL program from the shaders
        Shader shader("../assets/shaders/vs.shader", "../assets/shaders/fs.shader", Shader::READ_FILE_PATH);

        while (m_running)
        {
            m_window->OnUpdate();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //vertexarrayobject is bounded and it keeps all the attribute information
            vao.Bind();
            
            shader.Bind();
            // Draw the triangle !
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
    }

    void Application::OnEvent(Event & e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        CH_TRACE(e.ToString());
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_running = false;

        return false;
    }

}
