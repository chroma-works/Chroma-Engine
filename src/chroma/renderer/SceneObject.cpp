#include "SceneObject.h"
#include <thirdparty/glm/glm/gtc/matrix_transform.hpp>
#include <thirdparty/glm/glm/gtx/quaternion.hpp>

namespace Chroma
{
    SceneObject::SceneObject(Mesh mesh, std::string name, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
        : m_mesh(mesh), m_name(name), m_position(pos), m_rotation(glm::quat(rot)), m_scale(scale)
    {
        m_texture = Texture("../assets/textures/white.jpg");//Set texture to white to avoid all black shaded objects
    }

    void SceneObject::RecalculateModelMatrix()
    {
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_position);
        glm::mat4 rotation = glm::toMat4(m_rotation);
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_scale);

        m_model_matrix =  translation * rotation * scale ;
    }
}