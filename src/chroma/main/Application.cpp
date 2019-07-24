#pragma once

#include <thirdparty/glad/include/glad/glad.h>

#include "Application.h"

#include <chroma/main/Log.h>
#include <chroma/openGL/OpenGLBuffer.h>
#include <chroma/openGL/OpenGLVertexArrayObject.h>
#include <chroma/renderer/Shader.h>
#include <chroma/renderer/Camera.h>

#include <fstream>
#include <thirdparty/glm/glm/glm.hpp>
#include <thirdparty/glm//glm/gtc/matrix_transform.hpp>
#include <thirdparty/tinyobjloader/tiny_obj_loader.h>



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
        // vertex position array
        GLfloat vertices[] = {
             .5f, .5f, .5f, 1.0f,  -.5f, .5f, .5f, 1.0f,  -.5f,-.5f, .5f, 1.0f,  .5f,-.5f, .5f, 1.0f,// v0,v1,v2,v3 (front)
             .5f, .5f, .5f, 1.0f,  .5f,-.5f, .5f, 1.0f,  .5f,-.5f,-.5f, 1.0f,  .5f, .5f,-.5f, 1.0f,// v0,v3,v4,v5 (right)
             .5f, .5f, .5f, 1.0f,  .5f, .5f,-.5f, 1.0f,  -.5f, .5f,-.5f, 1.0f,  -.5f, .5f, .5f, 1.0f,// v0,v5,v6,v1 (top)
            -.5f, .5f, .5f, 1.0f,  -.5f, .5f,-.5f, 1.0f, -.5f,-.5f,-.5f, 1.0f, -.5f,-.5f, .5f, 1.0f,// v1,v6,v7,v2 (left)
            -.5f,-.5f,-.5f, 1.0f,  .5f,-.5f,-.5f, 1.0f,  .5f,-.5f, .5f, 1.0f, -.5f,-.5f, .5f, 1.0f,// v7,v4,v3,v2 (bottom)
             .5f,-.5f,-.5f, 1.0f, -.5f,-.5f,-.5f, 1.0f,  -.5f, .5f,-.5f, 1.0f,  .5f, .5f,-.5f, 1.0f  // v4,v7,v6,v5 (back)
        };

        // normal array
        GLfloat normals[] = {
             0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,  // v0,v1,v2,v3 (front)
             1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,  // v0,v3,v4,v5 (right)
             0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,  // v0,v5,v6,v1 (top)
            -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  // v1,v6,v7,v2 (left)
             0,-1, 0,   0,-1, 0,   0,-1, 0,   0,-1, 0,  // v7,v4,v3,v2 (bottom)
             0, 0,-1,   0, 0,-1,   0, 0,-1,   0, 0,-1   // v4,v7,v6,v5 (back)
        };

        // color array
        GLfloat colors[] = {
             1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 1.0f,  // v0,v1,v2,v3 (front)
             1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,  // v0,v3,v4,v5 (right)
             1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f,  // v0,v5,v6,v1 (top)
             1.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,  // v1,v6,v7,v2 (left)
             0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f,  // v7,v4,v3,v2 (bottom)
             0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 1.0f   // v4,v7,v6,v5 (back)
        };

        // texture coord array
        GLfloat texCoords[] = {
            1, 0,   0, 0,   0, 1,   1, 1,               // v0,v1,v2,v3 (front)
            0, 0,   0, 1,   1, 1,   1, 0,               // v0,v3,v4,v5 (right)
            1, 1,   1, 0,   0, 0,   0, 1,               // v0,v5,v6,v1 (top)
            1, 0,   0, 0,   0, 1,   1, 1,               // v1,v6,v7,v2 (left)
            0, 1,   1, 1,   1, 0,   0, 0,               // v7,v4,v3,v2 (bottom)
            0, 1,   1, 1,   1, 0,   0, 0                // v4,v7,v6,v5 (back)
        };

        GLuint indices[] = {
             0, 1, 2,   2, 3, 0,    // v0-v1-v2, v2-v3-v0 (front)
             4, 5, 6,   6, 7, 4,    // v0-v3-v4, v4-v5-v0 (right)
             8, 9,10,  10,11, 8,    // v0-v5-v6, v6-v1-v0 (top)
            12,13,14,  14,15,12,    // v1-v6-v7, v7-v2-v1 (left)
            16,17,18,  18,19,16,    // v7-v4-v3, v3-v2-v7 (bottom)
            20,21,22,  22,23,20     // v4-v7-v6, v6-v5-v4 (back)
        };

        // Create and compile our GLSL program from the shaders
        Shader* shader = Shader::ReadAndBuildShaderFromFile("../assets/shaders/vs.shader", "../assets/shaders/fs.shader");

        //Vertex positions buffer
        OpenGLVertexBuffer* vertex_buffer = new OpenGLVertexBuffer((void*)&vertices, sizeof(vertices) * sizeof(GLfloat));

        VertexAttribute layout_attribute("in_Position", 0, ShaderDataType::Float4, GL_FALSE);
        VertexBufferLayout vertex_buffer_layout;
        vertex_buffer_layout.PushAttribute(layout_attribute);
        vertex_buffer->SetBufferLayout(vertex_buffer_layout);

        //Vertex colors buffer
        OpenGLVertexBuffer* color_buffer = new OpenGLVertexBuffer((void*)&colors, sizeof(colors) * sizeof(GLfloat));

        VertexAttribute layout_attribute2("in_Color", 1, ShaderDataType::Float3, GL_FALSE);
        VertexBufferLayout vertex_buffer_layout2;
        vertex_buffer_layout2.PushAttribute(layout_attribute2);
        color_buffer->SetBufferLayout(vertex_buffer_layout2);

        //index buffer
        OpenGLIndexBuffer* index_buffer = new OpenGLIndexBuffer((void*)&indices, sizeof(indices));

        //vertex array object
        OpenGLVertexArrayObject vao;
        vao.AddVertexBuffer(vertex_buffer);
        vao.AddVertexBuffer(color_buffer);
        vao.SetIndexBuffer(index_buffer);

        vertex_buffer->Unbind();//To prove VAO works
        color_buffer->Unbind();
        index_buffer->Unbind();

        glEnable(GL_DEPTH_TEST);//TODO: Create an wrapper to encapsulate RenderCommand ??

        glm::mat4* model = new glm::mat4(1.0);
        *model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
        glm::mat4* view = new glm::mat4(1.0f);
        glm::mat4* proj = new glm::mat4(1.0f);

        PerspectiveCamera cam(1.0f * m_window->GetWidth(), 1.0f * m_window->GetHeight(), 0.1f, 100.0f);
        //OrthographicCamera cam2(-0.8f, 0.8f, -0.9, 0.9, -10, 10);
        cam.SetPosition({ 0.0f, 0.0f, 3.0f });
        //cam2.SetPosition({ 0.0f, 0.0f, 3.0f });
        
        //glm::vec4* light_pos = new glm::vec4(0.0f, 3.0f, 0.0f, 1.0f);

        shader->CreateUniform("u_Model", ShaderDataType::Mat4, model);
        shader->CreateUniform("u_View", ShaderDataType::Mat4, view);
        shader->CreateUniform("u_Proj", ShaderDataType::Mat4, proj);
        //shader->CreateUniform("u_LightPosition", ShaderDataType::Float4, light_pos);

        while (m_running)
        {
            *model = glm::rotate(*model, 0.03f, glm::vec3(0.0f, 1.0f, 0.3f));

            *proj = cam.GetProjectionMatrix();
            *view = cam.GetViewMatrix();

            m_window->OnUpdate();
            shader->UpdateUniforms();

            //vertexarrayobject is bounded and it keeps all the attribute information
            vao.Bind();
            shader->Bind();   
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glDrawElements(GL_TRIANGLES, index_buffer->GetSize(), GL_UNSIGNED_INT, NULL);
        }

        delete shader;
        delete vertex_buffer;
        delete color_buffer;
        delete index_buffer;

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
