#pragma once

#include <thirdparty/glm/glm/glm.hpp>
#include <vector>
namespace Chroma
{

    class Mesh
    {
    public:
        Mesh();
        Mesh(std::vector<glm::vec3> m_vertices, std::vector<glm::vec3> m_normals,
            std::vector<glm::vec2> m_texcoords, std::vector<glm::vec3> m_colors, unsigned int face_count);

        inline unsigned int GetFaceCount() const { return m_face_count; }
        inline unsigned int GetVertexCount() const { return m_vertex_count; }

        inline void SetFaceCount(unsigned int f_c) { m_face_count = f_c; }
        inline void GetVertexCount(unsigned int v_c) { m_vertex_count = v_c; }

        inline glm::vec3 GetMaxBound() const { return m_bound_max; }
        inline glm::vec3 GetMinBound() const { return m_bound_min; }

        inline std::vector<glm::vec3> GetVertices() const { return m_vertices; }
        inline std::vector<glm::vec3> GetNormals() const { return m_normals; }
        inline std::vector<glm::vec3> GetColors() const { return m_colors; }
        inline std::vector<glm::vec2> GetTexCoords() const { return m_texcoords; }

        inline void SetVertices(std::vector<glm::vec3> vertices) { m_vertices = vertices; CalculateBounds(); CenterToPivot(); }
        inline void SetNormals(std::vector<glm::vec3> normals) { m_normals = normals; }
        inline void SetColors(std::vector<glm::vec3> colors) { m_colors = colors; }
        inline void SetTexCoords(std::vector<glm::vec2> texcoords) { m_texcoords = texcoords; }


    private:
        void CenterToPivot();
        void CalculateBounds();

        unsigned int m_face_count = 0;
        unsigned int m_vertex_count = 0;

        glm::vec3 m_bound_max;
        glm::vec3 m_bound_min;

        std::vector<glm::vec3> m_vertices;
        std::vector<glm::vec3> m_normals;
        std::vector<glm::vec3> m_colors;
        std::vector<glm::vec2> m_texcoords;
    };
}