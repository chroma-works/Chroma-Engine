#include <Chroma.h>

class TestLayer : public Chroma::Layer
{
public:
    TestLayer()
    {
        glClearColor(0.184f, 0.062f, 0.129f, 1.0f);

        // Create and compile our GLSL program from the shaders
        Chroma::Shader* shader = Chroma::Shader::ReadAndBuildShaderFromFile("../assets/shaders/phong/phong.vert", "../assets/shaders/phong/phong.frag");

        //Model import
        Chroma::Mesh* r_mesh = Chroma::AssetImporter::LoadMeshFromOBJ("../assets/models/rabbit.obj");
        Chroma::Material* mat = new Chroma::Material("u_Material",
            glm::vec3({ 0.8f, 0.8f, 0.8f }), glm::vec3({ 0.8f, 0.8f, 0.8f }), glm::vec3({ 1.0f, 1.0f, 1.0f }), 90.0f);
        std::shared_ptr<Chroma::SceneObject> rabbit = std::make_shared<Chroma::SceneObject>(*r_mesh, "rabbit");

        //rabbit->SetTexture(*texture);
        rabbit->SetMaterial(*mat);

        Chroma::Mesh* b_mesh = Chroma::AssetImporter::LoadMeshFromOBJ("../assets/models/box.obj");
        Chroma::Texture* texture = new Chroma::Texture("../assets/textures/crate.jpg");
        std::shared_ptr<Chroma::SceneObject> box = std::make_shared<Chroma::SceneObject>(*b_mesh, "box");

        box->SetTexture(*texture);
        box->SetMaterial(*mat);

        m_scene = std::make_shared<Chroma::Scene>("The scene", shader);
        m_scene->AddSceneObject("rabbit", rabbit);
        m_scene->AddSceneObject("box", box);

        /*glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);*/
        glEnable(GL_DEPTH_TEST);//TODO: Create an wrapper to encapsulate RenderCommand ??

        Chroma::PerspectiveCamera* cam = new Chroma::PerspectiveCamera(1.0f * 1280,
            1.0f * 720, 0.1f, 300.0f);
        //OrthographicCamera cam2(-0.8f, 0.8f, -0.9, 0.9, -10, 10);
        cam->SetPosition({ -0.0f, 0.0f, -50.0f });
        m_scene->AddCamera("pers-cam", cam);
        //cam2.SetPosition({ 0.0f, 0.0f, 3.0f });

        std::shared_ptr<Chroma::PointLight> pl = std::make_shared<Chroma::PointLight>(glm::vec3(0.0f, 0.0f, 40.0f), glm::vec3(0.1f, 0.1f, 0.1f),
            glm::vec3(0.6f, 0.5f, 0.6f), glm::vec3(1.0f, 1.0f, 1.0f));

        std::shared_ptr<Chroma::DirectionalLight> dl = std::make_shared<Chroma::DirectionalLight>(glm::vec3(-30.0f, 0.0f, -40.0f),
            glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));

        std::shared_ptr<Chroma::SpotLight> sl = std::make_shared<Chroma::SpotLight>(glm::vec3(-20.0f, 0.0f, 40.0f), glm::vec3(0.0f, 0.0f, -1.0f),
            glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));

        glm::vec3* cam_pos = new glm::vec3(cam->GetPosition());

        //m_scene->AddLight("spot l", sl);
        //m_scene.AddLight("directional l", dl);
        m_scene->AddLight("point l", pl);
        glm::vec4 dir({ 0.0f, 0.0f, 0.0f, 1.0f });

        rabbit->SetScale({ .4f, .4f, .4f });
        rabbit->SetPosition({ 0.0f, -9.0f, 0.0f });
        rabbit->SetRotation(glm::quat({ glm::radians(-90.0f), glm::radians(90.0f), glm::radians(0.0f) }));

        box->SetScale({ .9f, .9f, .9f });
        box->SetPosition({ 35.0f, 0.0f, 0.0f });
        box->RotateAngleAxis(glm::radians(180.0), glm::vec3(0.0, 0.0, 1.0));
    }
    void OnUpdate(Chroma::Timestep ts) override
    {
        auto cam = m_scene->GetCamera("pers-cam");
        glm::vec3 forward = glm::normalize(cam->GetDirection() - cam->GetPosition());
        glm::vec3 right = glm::cross(forward, glm::normalize(cam->GetVectorUp()));

        if (Chroma::Input::IsKeyPressed(CH_KEY_W))
        {
            cam->SetPosition(cam->GetPosition() +  forward * m_camera_move_speed);
        }

        else if (Chroma::Input::IsKeyPressed(CH_KEY_S))
        {
            cam->SetPosition(cam->GetPosition() - forward * m_camera_move_speed);
        }

        if (Chroma::Input::IsKeyPressed(CH_KEY_A))
        {
            cam->SetPosition(cam->GetPosition() - glm::normalize(right) * m_camera_move_speed);
        }

        else if (Chroma::Input::IsKeyPressed(CH_KEY_D))
        {
            cam->SetPosition(cam->GetPosition() + glm::normalize(right) * m_camera_move_speed);
        }
        cam->SetDirection(cam->GetPosition() + glm::vec3(0.0, 0.0, 1.0f));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //rabbit->RotateAngleAxis(glm::radians(2.0f), glm::vec3(0.0, 1.0, 0.0));
        /*rabbit->Translate({ 0.1, 0.0, 0.0 });
        sl->position += glm::vec3({ 0.1, 0.0, 0.0 });
        cam->SetPosition(cam->GetPosition() + glm::vec3({ 0.1, 0.0, 0.0 }));
        cam->SetDirection(rabbit->GetPosition());*/

        m_scene->Render();
    }
    //~TestLayer();

private:
    std::shared_ptr<Chroma::Scene> m_scene;
    float m_camera_move_speed = 0.8f;

    float m_camera_rotation = 0.0f;
    float m_camera_rotation_speed = 180.0f;
};

class Sandbox : public Chroma::Application
{
public:
    Sandbox()
    {
        PushLayer(new TestLayer());
    }
    ~Sandbox()
    {}

};

Chroma::Application* Chroma::CreateApplication()
{
    return new Sandbox();
}
