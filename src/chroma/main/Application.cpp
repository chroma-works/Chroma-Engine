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

        //cube
        static const GLfloat g_vertex_buffer_data[] = {
        // front
        -1.0, -1.0, 1.0, 1.0, 1.0, 0.0, 0.0,
         1.0, -1.0, 1.0, 1.0, 0.0, 1.0, 0.0,
         1.0,  1.0, 1.0, 1.0, 0.0, 0.0, 1.0,
        -1.0,  1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        // back
        -1.0, -1.0, -1.0, 1.0, 1.0, 0.0, 0.0,
         1.0, -1.0, -1.0, 1.0, 0.0, 1.0, 0.0,
         1.0,  1.0, -1.0, 1.0, 0.0, 0.0, 1.0,
        -1.0,  1.0, -1.0, 1.0, 1.0, 1.0, 1.0
        };

        static const GLint g_index_buffer_data[] = {
        // front
        0, 1, 2,
        2, 3, 0,
        // right
        1, 5, 6,
        6, 2, 1,
        // back
        7, 6, 5,
        5, 4, 7,
        // left
        4, 0, 3,
        3, 7, 4,
        // bottom
        4, 5, 1,
        1, 0, 4,
        // top
        3, 2, 6,
        6, 7, 3 
        };

        //Vertex Array object
        OpenGLVertexArrayObject vao;
        //vertex buffer
        OpenGLVertexBuffer vertex_buffer((void*)&g_vertex_buffer_data, sizeof(g_vertex_buffer_data));

        //index buffer
        OpenGLIndexBuffer index_buffer((void*)&g_index_buffer_data, sizeof(g_index_buffer_data));

        //attributes vertex coords and colors
        VertexAttribute layout_attribute("vertex_coords", 0, ShaderDataType::Float4, GL_FALSE);
        VertexAttribute layout_attribute2("vertex_colors", 1, ShaderDataType::Float3, GL_FALSE);

        //Create Vertex Buffer Layout
        VertexBufferLayout vertex_buffer_layout;
        vertex_buffer_layout.PushAttribute(layout_attribute);
        vertex_buffer_layout.PushAttribute(layout_attribute2);

        //Give vertex buffer the layout
        vertex_buffer.SetBufferLayout(vertex_buffer_layout);
        vao.SetVertexBuffer(vertex_buffer);
        vao.SetIndexBuffer(index_buffer);

        vertex_buffer.Unbind();//To prove VAO works

        // Create and compile our GLSL program from the shaders
        Shader* shader = Shader::ReadAndBuildShaderFromFile("../assets/shaders/vs.shader", "../assets/shaders/fs.shader");

        glEnable(GL_DEPTH_TEST);

        float a = 0.0f;
        glm::mat4* model = new glm::mat4(1.0);
        *model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -0.0));
        glm::mat4* view = new glm::mat4(glm::lookAt(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
        glm::mat4* proj = new glm::mat4(glm::perspective(glm::radians(45.0f), 1.0f * m_window->GetWidth() / m_window->GetHeight(), 0.1f, 10.0f));


        shader->CreateUniform("u_Model", ShaderDataType::Mat4, model);
        shader->CreateUniform("u_View", ShaderDataType::Mat4, view);
        shader->CreateUniform("u_Proj", ShaderDataType::Mat4, proj);
        //shader->UpdateUniforms();

        while (m_running)
        {
            //*proj = glm::perspective(glm::radians(45.0f), 1.0f * m_window->GetWidth() / m_window->GetHeight(), 0.1f, 10.0f);
            *model = glm::rotate(*model, 0.03f, glm::vec3(0.0f, 1.0f, 0.3f));

            shader->UpdateUniforms();
            m_window->OnUpdate();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //vertexarrayobject is bounded and it keeps all the attribute information
            vao.Bind();
            shader->Bind();

            glDrawElements(GL_TRIANGLES, index_buffer.GetSize(), GL_UNSIGNED_INT, NULL);
        }

        delete shader;

    }

    void Application::OnEvent(Event & e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
        CH_TRACE(e.ToString());
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_running = false;

        return false;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        glViewport(0, 0, m_window->GetWidth(), m_window->GetHeight());

        return true;
    }

}
