#pragma once

#include <chroma/geometry/Mesh.h>
#include <chroma/renderer/Texture.h>
#include <chroma/renderer/Shader.h>

#include <string>
#include <thirdparty/glm/glm/glm.hpp>

namespace Chroma
{
    class SceneObject
    {
    public:
        SceneObject(Mesh mesh, std::string name,
            glm::vec3 m_pos = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3 m_rot = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3 m_scale = glm::vec3(1.0f, 1.0f, 1.0f));
        ~SceneObject();

        inline void HideInEditor(bool hide) { m_visible_in_editor = hide; }
        inline void SetVisible(bool visible) { m_visible = visible; }
        inline void SetPickable(bool pickable) { m_pickable = pickable; }

        inline bool IsVisibleInEditor() { return m_visible_in_editor; }
        inline bool IsVisible() { return m_visible; }
        inline bool IsPickable() { return m_pickable; }


        inline void SetPosition(glm::vec3 pos) { m_position = pos; RecalculateModelMatrix(); }
        inline void SetRotation(glm::vec3 rot) { m_rotation = rot; RecalculateModelMatrix(); }
        inline void SetScale(glm::vec3 sca) { m_scale = sca; RecalculateModelMatrix(); }

        inline glm::mat4 GetModelMatrix() { return m_model_matrix; }
        inline glm::vec3 GetPosition() { return m_position; }
        inline glm::vec3 GetRotation() { return m_rotation; }
        inline glm::vec3 GetScale() { return m_scale; }


        inline void SetTexture(Texture tex) { m_texture = tex; }
        inline void SetMaterial(Material mat) { m_material = mat; }


    private:
        void RecalculateModelMatrix();

        bool m_visible_in_editor = false;
        bool m_visible = true;
        bool m_pickable = true;

        std::string m_name;

        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_scale;

        glm::mat4 m_model_matrix = glm::mat4(1.0);

        Texture m_texture;
        Material m_material;
        Mesh m_mesh; //TODO: multiple mesh ?

    };
}