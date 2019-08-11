#pragma once

#include <thirdparty/glad/include/glad/glad.h>

#include "Application.h"

#include <chroma/main/AssetImporter.h>
#include <chroma/main/Log.h>
#include <chroma/openGL/OpenGLBuffer.h>
#include <chroma/openGL/OpenGLVertexArrayObject.h>
#include <chroma/renderer/Camera.h>
#include <chroma/renderer/Texture.h>
#include <chroma/renderer/SceneObject.h>
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

        //Model import
        Mesh* mesh = AssetImporter::LoadMeshFromOBJ("../assets/models/box.obj");
        Texture* texture = new Texture("../assets/textures/crate.jpg");
        Material* mat = new Material("u_Material",
            glm::vec3({ 0.8f, 0.8f, 0.8f }), glm::vec3({ 0.8f, 0.8f, 0.8f }), glm::vec3({ 0.8f, 0.8f, 0.8f }), 90.0f);
        SceneObject scnobj = SceneObject(*mesh, "rabbit");
        scnobj.SetTexture(*texture);
        scnobj.SetMaterial(*mat);
        
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
        PerspectiveCamera* cam = new PerspectiveCamera(1.0f * m_window->GetWidth(), 
            1.0f * m_window->GetHeight(), 0.1f, 300.0f);
        //OrthographicCamera cam2(-0.8f, 0.8f, -0.9, 0.9, -10, 10);
        cam->SetPosition({ 0.0f, 0.0f, 40.0f });
        //cam2.SetPosition({ 0.0f, 0.0f, 3.0f });
        
        PointLight* pl = new PointLight(glm::vec3(0.0f, 0.0f, 40.0f), glm::vec3(0.1f, 0.1f, 0.1f),
            glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));

        DirectionalLight* dl = new DirectionalLight(glm::vec3(-30.0f, 0.0f, -40.0f), 
            glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));

        SpotLight* sl = new SpotLight(glm::vec3(0.0f, 0.0f, 40.0f), glm::vec3(0.0f, 0.0f, -11.0f), 
            glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));

        glm::vec3* cam_pos = new glm::vec3(cam->GetPosition());

        shader->CreateUniform("u_Model", ShaderDataType::Mat4, model);
        shader->CreateUniform("u_View", ShaderDataType::Mat4, view);
        shader->CreateUniform("u_Proj", ShaderDataType::Mat4, proj);
        shader->CreateUniform("u_NormalMat", ShaderDataType::Mat4, normal_mat);
        //shader->AddLight(pl);
        //shader->AddLight(dl);
        shader->AddLight(sl);
        shader->CreateUniform(&scnobj.GetMaterial());
        shader->CreateUniform("u_CameraPos", ShaderDataType::Float3, cam_pos);
        glm::vec4 dir({ 0.0f, 0.0f, 0.0f, 1.0f });

        //scnobj.SetScale({ .7f, .7f, .7f });
        //scnobj.SetPosition({ 0.0f, -9.0f, 0.0f });
        scnobj.SetRotation(glm::quat({ glm::radians(0.0f), glm::radians(0.0f), glm::radians(0.0f) }));

        float a = 0.07f;

        while (m_running)
        {
            m_window->OnUpdate();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            scnobj.RotateAngleAxis(glm::radians(2.0f), glm::vec3(0.0, 1.0, 0.0));
            //dir = glm::rotate(glm::mat4(1.0f), a, glm::vec3(0.0f, 1.0f, 0.0f)) * dir;
            /*cam->SetPosition(glm::rotate(glm::mat4(1.0f), a, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(cam->GetPosition(), 1.0f));
            cam->SetDirection(dir);*/
            
            *cam_pos = cam->GetPosition();
            *proj = cam->GetProjectionMatrix();
            *view = cam->GetViewMatrix();
            *model = scnobj.GetModelMatrix();
            *normal_mat = (glm::transpose(glm::inverse(*model)));

            shader->UpdateUniforms();
            shader->Bind();


            scnobj.SetPosition({ -13.0, 0.0f, 0.0f });
            *model = scnobj.GetModelMatrix();
            *normal_mat = (glm::transpose(glm::inverse(*model)));
            shader->UpdateUniforms();

            scnobj.Draw(DrawMode::TRI);


            scnobj.SetPosition({ 13.0, 0.0f, 0.0f });
            *model = scnobj.GetModelMatrix();
            *normal_mat = (glm::transpose(glm::inverse(*model)));
            shader->UpdateUniforms();

            scnobj.Draw(DrawMode::TRI);
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
