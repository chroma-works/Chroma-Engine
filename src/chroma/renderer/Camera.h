#pragma once

//from:https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Renderer/OrthographicCamera.h
#include <thirdparty/glm/glm/glm.hpp>

namespace Chroma
{
    class Camera
    {
    public:
        const glm::vec3& GetPosition() const { return m_position; }
        void SetPosition(const glm::vec3& position) { m_position = position; RecalculateViewMatrix(); }

        const glm::vec3& GetDirection() const { return m_direction; }
        void SetDirection(const glm::vec3& direction) { m_direction = direction; RecalculateViewMatrix(); }

        const glm::vec3& GetVectorUp() const { return m_vector_up; }
        void SetVectorUp(const glm::vec3& vector) { m_vector_up = vector; RecalculateViewMatrix(); }

        const glm::mat4& GetProjectionMatrix() const { return m_projection_matrix; }
        const glm::mat4& GetViewMatrix() const { return m_view_matrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_view_projection_matrix; }

    protected:
        virtual void RecalculateViewMatrix() = 0;

        glm::mat4 m_projection_matrix;
        glm::mat4 m_view_matrix;
        glm::mat4 m_view_projection_matrix;

        glm::vec3 m_position = {0.0f, 0.0f, 0.0f};
        glm::vec3 m_direction = { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_vector_up = { 0.0f, 1.0f, 0.0f };

    };

    class OrthographicCamera : public Camera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0f);
        void RecalculateViewMatrix() override;
    };

    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera(float width, float height, float near, float far, float fov = 45.0f);

        float GetFOV() { return m_fov; }
        void SetFOV(float fov) { m_fov = fov; }

        void RecalculateViewMatrix() override;

    private:
        float m_fov;

    };

}

