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
        Mesh* r_mesh = AssetImporter::LoadMeshFromOBJ("../assets/models/rabbit.obj");
        Material* mat = new Material("u_Material",
            glm::vec3({ 0.8f, 0.8f, 0.8f }), glm::vec3({ 0.8f, 0.8f, 0.8f }), glm::vec3({ 1.0f, 1.0f, 1.0f }), 90.0f);
        std::shared_ptr<SceneObject> rabbit = std::make_shared<SceneObject>(*r_mesh, "rabbit");

        //rabbit->SetTexture(*texture);
        rabbit->SetMaterial(*mat);

        Mesh* b_mesh = AssetImporter::LoadMeshFromOBJ("../assets/models/box.obj");
        Texture* texture = new Texture("../assets/textures/crate.jpg");
        std::shared_ptr<SceneObject> box = std::make_shared<SceneObject>(*b_mesh, "box");

        box->SetTexture(*texture);
        box->SetMaterial(*mat);

        Scene scene("The scene", shader);
        scene.AddSceneObject("rabbit", rabbit);
        scene.AddSceneObject("box", box);

        /*glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);*/
        glEnable(GL_DEPTH_TEST);//TODO: Create an wrapper to encapsulate RenderCommand ??

        glm::mat4* model = new glm::mat4(1.0);
        *model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0f));
        //*model = glm::rotate(*model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4* view = new glm::mat4(1.0f);
        glm::mat4* proj = new glm::mat4(1.0f);
        glm::mat4* normal_mat = new glm::mat4(1.0f);

        PerspectiveCamera* cam = new PerspectiveCamera(1.0f * m_window->GetWidth(),
            1.0f * m_window->GetHeight(), 0.1f, 300.0f);
        //OrthographicCamera cam2(-0.8f, 0.8f, -0.9, 0.9, -10, 10);
        cam->SetPosition({ -20.0f, 10.0f, 50.0f });
        scene.AddCamera("pers-cam", cam);
        //cam2.SetPosition({ 0.0f, 0.0f, 3.0f });

        std::shared_ptr<PointLight> pl = std::make_shared<PointLight>(glm::vec3(0.0f, 0.0f, 40.0f), glm::vec3(0.1f, 0.1f, 0.1f),
            glm::vec3(0.6f, 0.5f, 0.6f), glm::vec3(1.0f, 1.0f, 1.0f));

        std::shared_ptr<DirectionalLight> dl = std::make_shared<DirectionalLight>(glm::vec3(-30.0f, 0.0f, -40.0f),
            glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));

        std::shared_ptr<SpotLight> sl = std::make_shared<SpotLight>(glm::vec3(-20.0f, 0.0f, 40.0f), glm::vec3(0.0f, 0.0f, -1.0f),
            glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));

        glm::vec3* cam_pos = new glm::vec3(cam->GetPosition());

        scene.AddLight("spot l", sl);
        //scene.AddLight("directional l", dl);
        //scene.AddLight("point l", pl);
        glm::vec4 dir({ 0.0f, 0.0f, 0.0f, 1.0f });

        rabbit->SetScale({ .4f, .4f, .4f });
        rabbit->SetPosition({ -20.0f, -9.0f, 0.0f });
        rabbit->SetRotation(glm::quat({ glm::radians(-90.0f), glm::radians(90.0f), glm::radians(0.0f) }));

        box->SetScale({ .9f, .9f, .9f });
        box->SetPosition({ 35.0f, 0.0f, 0.0f });
        box->RotateAngleAxis(glm::radians(180.0), glm::vec3(0.0, 0.0, 1.0));

        float a = 0.07f;

        while (m_running)
        {
            m_window->OnUpdate();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            //rabbit->RotateAngleAxis(glm::radians(2.0f), glm::vec3(0.0, 1.0, 0.0));
            rabbit->Translate({0.1, 0.0, 0.0});
            sl->position += glm::vec3({ 0.1, 0.0, 0.0 });
            cam->SetPosition(cam->GetPosition() + glm::vec3({ 0.1, 0.0, 0.0 }));
            cam->SetDirection(rabbit->GetPosition());

            scene.Render();
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
