#pragma once

#include <thirdparty/glad/include/glad/glad.h>
#include "Application.h"
#include <chroma/main/Log.h>
#include <chroma/renderer/Shader.h>
#include <fstream>

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
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
        };

        // This will identify our vertex buffer
        GLuint vertexbuffer;
        // Generate 1 buffer, put the resulting identifier in vertexbuffer
        glGenBuffers(1, &vertexbuffer);
        // The following commands will talk about our 'vertexbuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        // Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        // Create and compile our GLSL program from the shaders
        Shader shader("../assets/shaders/vs.shader", "../assets/shaders/fs.shader", Shader::READ_FILE_PATH);

        while (m_running)
        {
            m_window->OnUpdate();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // 1st attribute buffer : vertices
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
            );
            shader.Bind();
            // Draw the triangle !
            glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
            //glDisableVertexAttribArray(0);
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
