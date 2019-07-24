#include "Mesh.h"

Mesh::Mesh()
{}

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> texcoords, std::vector<glm::vec3> colors, unsigned int face_count)
{
    m_vertices = vertices;
    m_normals = normals;
    m_colors = colors;
    m_texcoords = texcoords;

    m_vertex_count = vertices.size();
    m_face_count = face_count;
}

void Mesh::CenterToPivot()
{
    glm::vec3 center(0, 0, 0);

    for (int i = 0; i < m_vertex_count; i++)
        center += m_vertices[i] / (1.0f * m_vertex_count);

    for (int i = 0; i < m_vertex_count; i++)
        m_vertices[i] -= center;

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
        m_bound_min = m_vertices[0];
        m_bound_max = m_vertices[0];

        for (int i = 0; i < m_vertex_count; i++)
        {
            m_bound_min = glm::min(m_vertices[i], m_bound_min);
            m_bound_max = glm::max(m_vertices[i], m_bound_max);
        }
    }
}
