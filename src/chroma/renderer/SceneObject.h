#pragma once

#include <chroma/geometry/Mesh.h>
#include <chroma/renderer/Texture.h>
#include <chroma/renderer/Shader.h>

#include <string>
#include <thirdparty/glm/glm/glm.hpp>
#include <thirdparty/glm/glm/gtc/quaternion.hpp>
#include <thirdparty/glm/glm/gtx/euler_angles.hpp>

namespace Chroma
{
    class SceneObject
    {
    public:
        SceneObject(Mesh mesh, std::string name,
            glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3 rot = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
        //~SceneObject();

        inline void HideInEditor(bool hide) { m_visible_in_editor = hide; }
        inline void SetVisible(bool visible) { m_visible = visible; }
        inline void SetPickable(bool pickable) { m_pickable = pickable; }

        inline bool IsVisibleInEditor() const { return m_visible_in_editor; }
        inline bool IsVisible() const { return m_visible; }
        inline bool IsPickable() const { return m_pickable; }


        inline void SetPosition(const glm::vec3 pos) { m_position = pos; RecalculateModelMatrix(); }
        inline void SetRotation(const glm::quat rot) { m_rotation = rot; RecalculateModelMatrix(); }
        inline void SetScale(const glm::vec3 sca) { m_scale = sca; RecalculateModelMatrix(); }

        inline glm::mat4 GetModelMatrix() const { return m_model_matrix; }
        inline glm::vec3 GetPosition() const { return m_position; }
        inline glm::quat GetRotation() const { return m_rotation; }
        inline glm::vec3 GetScale() const { return m_scale; }

        inline void Translate(const glm::vec3 vec) { m_position += vec; RecalculateModelMatrix(); }
        inline void RotateAngleAxis(const float angle, const glm::vec3 axis) { m_rotation = glm::angleAxis(angle, axis) * m_rotation; 
            RecalculateModelMatrix();}
        inline void RotateEuler( const glm::vec3 euler_angles) { m_rotation = glm::quat(euler_angles) * m_rotation; 
            RecalculateModelMatrix();}
        inline void Scale(const glm::vec3 scale) { m_scale *= scale; RecalculateModelMatrix(); }
        inline void ResetTransforms() { m_model_matrix = glm::mat4(1.0f); }


        inline void SetTexture(Texture tex) { m_texture = tex; }
        inline void SetMaterial(Material mat) { m_material = mat; }

        inline Material GetMaterial() { return m_material; }


    private:
        void RecalculateModelMatrix();

        bool m_visible_in_editor = false;
        bool m_visible = true;
        bool m_pickable = true;

        std::string m_name;

        glm::vec3 m_position;
        glm::quat m_rotation;
        glm::vec3 m_scale;

        glm::mat4 m_model_matrix = glm::mat4(1.0);

        Texture m_texture;
        Material m_material = Material("u_Material", glm::vec3(1.0f, 1.0f, 1.0f), 
            glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f), 80.0f);
        Mesh m_mesh; //TODO: multiple mesh ?

    };
}