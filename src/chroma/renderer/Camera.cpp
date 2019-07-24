
#include "Camera.h"

#include <algorithm>

namespace Chroma
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near_clip, float far_clip)
    {
        m_projection_matrix = glm::ortho(left, right, bottom, top, near_clip, far_clip);
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

    PerspectiveCamera::PerspectiveCamera(float width, float height, float near_clip, float far_clip, float fov)
    {
        m_projection_matrix = glm::perspective(glm::radians(fov), (width/height), near_clip, far_clip);
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

    void CameraManager::SetCamera(std::string id, bool active)
    {
        Camera* selected_cam;
        try
        {
            selected_cam = m_cameras.at(id);
        }
        catch (std::out_of_range& const e)
        {
            std::string err = "Camera with id: " + id + " cannot be found";
            CH_ERROR(err + e.what());
            return;
        }

        if(active)
        {
            m_active_cameras.push_back(selected_cam);
        }
        else
        {
            if (std::find(m_active_cameras.begin(), m_active_cameras.end(), selected_cam)  != m_active_cameras.end())
            {
                m_active_cameras.erase(std::remove(m_active_cameras.begin(), m_active_cameras.end(), selected_cam), m_active_cameras.end());
            }
            else
            {
                std::string msg = "Camera with id: " + id + " is not active";
                CH_WARN(msg);
            }
        }

    }

}