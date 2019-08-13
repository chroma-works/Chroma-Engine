#include "Scene.h"

namespace Chroma
{
    Scene::Scene(std::string name, Shader* shader)
        : m_name(name)
    {
        m_scene_data = new SceneData(shader);

        m_scene_data->m_shader->Bind();
        m_scene_data->m_shader->CreateUniform(Shader::MODEL_SH, ShaderDataType::Mat4, m_scene_data->GetModel());
        m_scene_data->m_shader->CreateUniform(Shader::VIEW_SH, ShaderDataType::Mat4, m_scene_data->GetView());
        m_scene_data->m_shader->CreateUniform(Shader::PROJ_SH, ShaderDataType::Mat4, m_scene_data->GetProj());
        m_scene_data->m_shader->CreateUniform(Shader::NORM_MAT_SH, ShaderDataType::Mat4, m_scene_data->GetNormalMat());
        m_scene_data->m_shader->CreateUniform(Shader::CAM_POS_SH, ShaderDataType::Float3, m_scene_data->GetCamPos());
    }

    Scene::~Scene()
    {
        delete m_scene_data;
        //delete[] m_cameras;//TODO!!!
    }

    void Scene::AddSceneObject(std::string name, std::shared_ptr<SceneObject> object)
    {
        m_scene_objects[name] = object;
    }

    void Scene::AddCamera(std::string name, Camera* cam)
    {
        m_cameras[name] = cam;
    }

    void Scene::AddLight(std::string name, std::shared_ptr<DirectionalLight> li)
    {
        m_dir_lights[name] = li;
        m_scene_data->m_shader->AddLight(li);
    }

    void Scene::AddLight(std::string name, std::shared_ptr<PointLight> li)
    {
        m_point_lights[name] = li;
        m_scene_data->m_shader->AddLight(li);
    }

    void Scene::AddLight(std::string name, std::shared_ptr<SpotLight> li)
    {
        m_spot_lights[name] = li;
        m_scene_data->m_shader->AddLight(li);
    }
    void Scene::Render(DrawMode mode)
    {
        //TODO:Render for multiple cams
        m_scene_data->SetView(m_cameras.begin()->second->GetViewMatrix());
        m_scene_data->SetProj(m_cameras.begin()->second->GetProjectionMatrix());
        for (std::pair<std::string, std::shared_ptr<SceneObject>> element : m_scene_objects)
        {
            std::shared_ptr<SceneObject> scn_obj = element.second;
            
            m_scene_data->SetModel(scn_obj->GetModelMatrix());
            m_scene_data->SetMaterial(&scn_obj->GetMaterial());

            m_scene_data->m_shader->UpdateUniforms();
            m_scene_data->m_shader->Bind();
            scn_obj->Draw(mode);
        }
    }
}