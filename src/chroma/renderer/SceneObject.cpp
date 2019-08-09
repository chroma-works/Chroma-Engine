#include "SceneObject.h"
#include <thirdparty/glm//glm/gtc/matrix_transform.hpp>

namespace Chroma
{
    void SceneObject::RecalculateModelMatrix()
    {
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_position);
        //glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), m_rotation.x, glm::vec3);
        //INCOMPLETE
    }
}