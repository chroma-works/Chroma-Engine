#pragma once

#include <thirdparty/glad/include/glad/glad.h>

#include "Application.h"

#include <chroma/main/AssetImporter.h>
#include <chroma/main/Log.h>
#include <chroma/openGL/OpenGLBuffer.h>
#include <chroma/openGL/OpenGLVertexArrayObject.h>
#include <chroma/renderer/Camera.h>
#include <chroma/renderer/Texture.h>
#include <chroma/renderer/Shader.h>

#include <fstream>
#include <string>
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

        // Create and compile our GLSL program from the shaders
        Shader* shader = Shader::ReadAndBuildShaderFromFile("../assets/shaders/phong/phong.vert", "../assets/shaders/phong/phong.frag");

        //Model import test
        Mesh* mesh = AssetImporter::LoadMeshFromOBJ("../assets/models/box.obj");
        Texture* texture = new Texture("../assets/textures/tarmac.jpg");

        //Vertex positions buffer
        OpenGLVertexBuffer* vertex_buffer = new OpenGLVertexBuffer((void*)mesh->m_vertex_positions.data(), 
            mesh->m_vertex_positions.size() * sizeof(GLfloat) * 3);

        VertexAttribute layout_attribute("in_Position", 0, ShaderDataType::Float3, GL_FALSE);
        VertexBufferLayout vertex_buffer_layout;
        vertex_buffer_layout.PushAttribute(layout_attribute);
        vertex_buffer->SetBufferLayout(vertex_buffer_layout);

        //Vertex normals buffer
        OpenGLVertexBuffer* normal_buffer = new OpenGLVertexBuffer((void*)mesh->m_vertex_normals.data(),
            mesh->m_vertex_normals.size() * sizeof(GLfloat) * 3);

        VertexAttribute layout_attribute2("in_Normal", 1, ShaderDataType::Float3, GL_FALSE);
        VertexBufferLayout vertex_buffer_layout2;
        vertex_buffer_layout2.PushAttribute(layout_attribute2);
        normal_buffer->SetBufferLayout(vertex_buffer_layout2);

        //Vertex colors buffer
        OpenGLVertexBuffer* tex_coord_buffer = new OpenGLVertexBuffer((void*)mesh->m_vertex_texcoords.data(),
            mesh->m_vertex_texcoords.size() * sizeof(GLfloat) * 2);

        VertexAttribute layout_attribute3("in_TexCoord", 2, ShaderDataType::Float2, GL_FALSE);
        VertexBufferLayout vertex_buffer_layout3;
        vertex_buffer_layout3.PushAttribute(layout_attribute3);
        tex_coord_buffer->SetBufferLayout(vertex_buffer_layout3);

        //index buffer
        OpenGLIndexBuffer* index_buffer = new OpenGLIndexBuffer(mesh->m_indices.data(),mesh->m_indices.size());
        //OpenGLIndexBuffer* index_buffer = new OpenGLIndexBuffer(indices, 36);

        //vertex array object
        OpenGLVertexArrayObject vao;
        vao.AddVertexBuffer(vertex_buffer);
        vao.AddVertexBuffer(normal_buffer);
        vao.AddVertexBuffer(tex_coord_buffer);
        vao.SetIndexBuffer(index_buffer);

        vertex_buffer->Unbind();//To prove VAO works
        normal_buffer->Unbind();
        index_buffer->Unbind();
        
        /*glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);*/
        glEnable(GL_DEPTH_TEST);//TODO: Create an wrapper to encapsulate RenderCommand ??

        glm::mat4* model = new glm::mat4(1.0);
        *model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0f));
        //*model = glm::rotate(*model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4* view = new glm::mat4(1.0f);
        glm::mat4* proj = new glm::mat4(1.0f);
        glm::mat4* normal_mat = new glm::mat4(1.0f);

        CameraManager* cam_mngr = CameraManager::GetInstance();
        PerspectiveCamera* cam = new PerspectiveCamera(1.0f * m_window->GetWidth(), 1.0f * m_window->GetHeight(), 0.1f, 300.0f);
        //OrthographicCamera cam2(-0.8f, 0.8f, -0.9, 0.9, -10, 10);
        cam->SetPosition({ 0.0f, 0.0f, 40.0f });
        //cam2.SetPosition({ 0.0f, 0.0f, 3.0f });
        
        glm::vec3* light_pos = new glm::vec3(0.0f, 0.0f, 40.0f);
        PointLight* pl = new PointLight(*light_pos, glm::vec3(0.1f, 0.1f, 0.1f),
            glm::vec3(0.5f, 0.3f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

        glm::vec3* light_dir = new glm::vec3(-30.0f, 0.0f, -40.0f);
        DirectionalLight* dl = new DirectionalLight(*light_dir, glm::vec3(0.1f, 0.1f, 0.1f),
            glm::vec3(0.5f, 0.3f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

        glm::vec3* light_pos2 = new glm::vec3(0.0f, 0.0f, 40.0f);
        glm::vec3* light_dir2 = new glm::vec3(0.0f, 0.0f, -11.0f);
        SpotLight* sl = new SpotLight(*light_pos2, *light_dir2, glm::vec3(0.1f, 0.1f, 0.1f), 
            glm::vec3(0.5f, 0.3f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

        glm::vec3* cam_pos = new glm::vec3(cam->GetPosition());

        shader->CreateUniform("u_Model", ShaderDataType::Mat4, model);
        shader->CreateUniform("u_View", ShaderDataType::Mat4, view);
        shader->CreateUniform("u_Proj", ShaderDataType::Mat4, proj);
        shader->CreateUniform("u_NormalMat", ShaderDataType::Mat4, normal_mat);
        //shader->AddLight(pl);
        //shader->AddLight(dl);
        shader->AddLight(sl);
        shader->CreateUniform(new Material("u_Material",
            new glm::vec3({1.00f, 1.0f, 1.0f }), new glm::vec3({ 0.5f, 0.5f, .5f }), new glm::vec3({ 1.0f, 1.0f, 1.0f }), 60.0f));
        glm::vec4 dir({ 0.0f, 0.0f, 0.0f, 1.0f });
        shader->CreateUniform("u_CameraPos", ShaderDataType::Float3, cam_pos);

        float a = 0.04f;

        while (m_running)
        {
            //*model = glm::rotate(*model, 0.039f, glm::vec3(0.0f, 1.0f, 0.0f));
            //dir = glm::rotate(glm::mat4(1.0f), a, glm::vec3(0.0f, 1.0f, 0.0f)) * dir;
            //*light_pos = glm::rotate(glm::mat4(1.0f), a, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(*light_pos, 1.0f);
            /*cam->SetPosition(glm::rotate(glm::mat4(1.0f), a, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(cam->GetPosition(), 1.0f));
            cam->SetDirection(dir);*/
            *cam_pos = cam->GetPosition();

            *proj = cam->GetProjectionMatrix();
            *view = cam->GetViewMatrix();
            *normal_mat = (glm::transpose(glm::inverse( *model)));

            m_window->OnUpdate();
            shader->UpdateUniforms();

            //vertexarrayobject is bounded and it keeps all the attribute information
            vao.Bind();
            shader->Bind();
            texture->Bind();
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glDrawElements(GL_TRIANGLES, index_buffer->GetSize(), GL_UNSIGNED_INT, NULL);
        }

        delete shader;
        delete vertex_buffer;
        delete normal_buffer;
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
