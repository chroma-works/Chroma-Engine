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
        -1.0f, -1.0f, 0.0f, 1.0f,  1.0f,  0.0f,
        1.0f, -1.0f, 0.0f, 1.0f,  1.0f,  0.0f,
        1.0f,  1.0f, 0.0f, 0.0f,  0.0f,  1.0f,
        -1.0f,  1.0f, 0.0f, 0.0f,  1.0f,  1.0f,
        };

        static const GLint g_index_buffer_data[] = {0, 3, 2, 2, 1, 0};


        //Vertex Array object
        OpenGLVertexArrayObject vao;
        //vertex buffer
        OpenGLVertexBuffer vertex_buffer((void*)&g_vertex_buffer_data, sizeof(g_vertex_buffer_data));

        //index buffer
        OpenGLIndexBuffer index_buffer((void*)&g_index_buffer_data, sizeof(g_index_buffer_data));

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
        vao.SetIndexBuffer(index_buffer);

        vertex_buffer.Unbind();//To prove VAO works

        // Create and compile our GLSL program from the shaders
        Shader* shader = Shader::ReadAndBuildShaderFromFile("../assets/shaders/vs.shader", "../assets/shaders/fs.shader");
        std::shared_ptr <glm::vec3> uniform_testcolor(new glm::vec3(1.0f, 0.0f, 0.0f));
        /*shader->Bind();
        int location = glGetUniformLocation(1, "testcolor");
        glUniform3f(location, 0.0f, 0.0f, 1.0f);*/

        float* data = new float[3];
        data[0] = 0.0f;
        data[1] = 0.0f;
        data[2] = 1.0f;
        //auto data = std::make_shared<float>(5.1);
        /*Uniform uniform("testcolor", ShaderDataType::Float3);
        uniform.data = data;*/
        glm::mat4* Model = new glm::mat4(1.0); ;
        *Model = glm::rotate(*Model, 1.00f, glm::vec3(0.0f, 0.0f, 1.0f));


        shader->CreateUniform("testcolor", ShaderDataType::Float3, data);
        shader->CreateUniform("u_Model", ShaderDataType::Mat4, Model);
        shader->UpdateUniforms();

        //shader->AddUniform(uniform);
        float sign = 1.0f;
        while (m_running)
        {
            sign = data[0] > 1.0f || data[0] < 0.0f ? -sign : sign;
            data[0] += sign*0.01f;
            *Model = glm::rotate(*Model, 0.01f, glm::vec3(0.0f, 0.5f, 1.0f));

            shader->UpdateUniforms();
            m_window->OnUpdate();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //vertexarrayobject is bounded and it keeps all the attribute information
            vao.Bind();

            shader->Bind();
            // Draw the triangle !
            glDrawElements(GL_TRIANGLES, index_buffer.GetSize(), GL_UNSIGNED_INT, NULL);
        }
        delete shader;
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
