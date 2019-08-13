#pragma once

#include <chroma/renderer/Camera.h>
#include <chroma/renderer/Light.h>
#include <chroma/renderer/SceneObject.h>

#include <stdio.h>
#include <map>
#include <vector>


namespace Chroma
{
class Camera;
    class Scene
    {
    public:
        Scene(std::string name, Shader* shader);
        ~Scene();

        void AddSceneObject(std::string name, std::shared_ptr<SceneObject> object);
        void AddCamera(std::string name, Camera* cam);

        std::shared_ptr<SceneObject> GetSceneObject(std::string name) { return m_scene_objects[name]; }
        Camera* GetCamera(std::string name) { return m_cameras[name]; }


        void AddLight(std::string name, std::shared_ptr<DirectionalLight> li);
        void AddLight(std::string name, std::shared_ptr<PointLight> li);
        void AddLight(std::string name, std::shared_ptr<SpotLight> li);

        inline std::shared_ptr<DirectionalLight> GetDirectionalLight(std::string name) { return m_dir_lights[name]; } //TODO: add null check
        inline std::shared_ptr<PointLight> GetPointLight(std::string name) { return m_point_lights[name]; }
        inline std::shared_ptr<SpotLight> GetSpotlLight(std::string name) { return m_spot_lights[name]; }


        void Render(DrawMode = DrawMode::TRI);

    private:
        std::string m_name;

        std::map<std::string, std::shared_ptr<SceneObject>> m_scene_objects;
        std::map<std::string, Camera*> m_cameras;

        std::map<std::string, std::shared_ptr<DirectionalLight>> m_dir_lights;
        std::map<std::string, std::shared_ptr<PointLight>> m_point_lights;
        std::map<std::string, std::shared_ptr<SpotLight>> m_spot_lights;

        class SceneData
        {
            //friend class Scene;
        public:
            SceneData(Shader* shader)
                :m_shader(shader)
            {}

            inline void SetModel(glm::mat4 mat) 
            {
                *m_model = mat;
                *m_normal_mat = (glm::transpose(glm::inverse(*m_model)));
                //m_shader.UpdateUniforms();
            }
            inline void SetView(glm::mat4 mat)
            {
                *m_view = mat;
                //m_shader.UpdateUniforms();
            }
            inline void SetProj(glm::mat4 mat)
            {
                *m_proj = mat;
                //m_shader.UpdateUniforms();
            }
            inline void SetMaterial(Material* material)
            {
                m_material = material;
            }
            inline void SetCamPos(glm::vec3 cam_pos)
            {
                *m_cam_pos = cam_pos;
            }

            inline glm::mat4* GetModel() { return m_model; }
            inline glm::mat4* GetView() { return m_view; }
            inline glm::mat4* GetProj() { return m_proj; }
            inline glm::mat4* GetNormalMat() { return m_normal_mat; }
            inline Material* GetMaterial() { return m_material; }
            inline glm::vec3* GetCamPos() { return m_cam_pos; }

            Shader* m_shader;
        private:
            glm::mat4* m_model = new glm::mat4(1.0f);
            glm::mat4* m_view = new glm::mat4(1.0f);
            glm::mat4* m_proj = new glm::mat4(1.0f);
            glm::mat4* m_normal_mat = new glm::mat4(1.0f);
            Material* m_material;
            glm::vec3* m_cam_pos = new glm::vec3(0.0f);
        };
        SceneData* m_scene_data;
    };
}