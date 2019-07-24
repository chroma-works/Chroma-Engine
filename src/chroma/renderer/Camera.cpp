
#include "Camera.h"
#include <thirdparty/glm//glm/gtc/matrix_transform.hpp>

namespace Chroma
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    {
        m_projection_matrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_view_matrix = glm::mat4(1.0f);
        m_view_projection_matrix = m_projection_matrix * m_view_matrix;
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) /**
            glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1))*/;

        m_view_matrix = glm::lookAt(m_position, m_direction, m_vector_up);
        m_view_projection_matrix = m_projection_matrix * m_view_matrix;
    }

    PerspectiveCamera::PerspectiveCamera(float width, float height, float near, float far, float fov)
    {
        m_projection_matrix = glm::perspective(glm::radians(fov), (width/height), near, far);
        m_view_matrix = glm::mat4(1.0f);
        m_view_projection_matrix = m_projection_matrix * m_view_matrix;
    }

    void PerspectiveCamera::RecalculateViewMatrix()
    {
        /*glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) /**
            glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1))*/;

        m_view_matrix = glm::lookAt(m_position, m_direction, m_vector_up);
        m_view_projection_matrix = m_projection_matrix * m_view_matrix;
    }

}