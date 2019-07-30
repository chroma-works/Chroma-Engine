#include "Mesh.h"
namespace Chroma
{

    Mesh::Mesh()
    {
        m_bound_min = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
        m_bound_max = { std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min() };
    }

    Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> texcoords, std::vector<glm::vec3> colors, unsigned int face_count)
    {
        m_vertex_positions = vertices;
        m_vertex_normals = normals;
        m_vertex_colors = colors;
        m_vertex_texcoords = texcoords;

        m_vertex_count = vertices.size();
        m_face_count = face_count;

        m_bound_min = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
        m_bound_max = { std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min() };

        CalculateBounds();
        CenterToPivot();
    }

    void Mesh::CenterToPivot()
    {
        glm::vec3 center(0, 0, 0);

        for (int i = 0; i < m_vertex_count; i++)
            center += m_vertex_positions[i] / (1.0f * m_vertex_count);

        for (int i = 0; i < m_vertex_count; i++)
            m_vertex_positions[i] -= center;

        m_bound_max -= center;
        m_bound_min -= center;
    }

    void Mesh::CalculateBounds()
    {
        if (m_vertex_count == 0)
        {
            m_bound_min = glm::vec3(0);
            m_bound_max = glm::vec3(0);
        }
        else
        {
            m_bound_min = m_vertex_positions[0];
            m_bound_max = m_vertex_positions[0];

            for (int i = 0; i < m_vertex_count; i++)
            {
                m_bound_min = glm::min(m_vertex_positions[i], m_bound_min);
                m_bound_max = glm::max(m_vertex_positions[i], m_bound_max);
            }
        }
    }

}