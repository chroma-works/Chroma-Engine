#pragma once

#include <limits>
#include <thirdparty/glm/glm/glm.hpp>
#include <vector>


namespace Chroma
{
#define VECTOR_FIELD_METHODS(VAR, NAME_S, NAME_P, TYPE) std::vector<TYPE> Get##NAME_P() const { return VAR; }\
                                                    void Set##NAME_P(std::vector<TYPE> NAME) { VAR = NAME;}\
                                                    void AddTo##NAME_P(TYPE val) { VAR.push_back(val);}\
                                                    void ResizeSpaceFrom##NAME_P(unsigned int size) {VAR.resize(size);}\
                                                    void Set##NAME_S##At(unsigned int index, TYPE val) {VAR.at(index) = val;}

    class Mesh
    {
    public:
        Mesh();
        Mesh(std::vector<glm::vec3> m_vertices, std::vector<glm::vec3> m_normals,
            std::vector<glm::vec2> m_texcoords, std::vector<glm::vec3> m_colors, unsigned int face_count);

        inline unsigned int GetFaceCount() const { return m_face_count; }
        inline unsigned int GetVertexCount() const { return m_vertex_count; }

        inline void SetFaceCount(unsigned int f_c) { m_face_count = f_c; }
        inline void SetVertexCount(unsigned int v_c) { m_vertex_count = v_c; }

        inline glm::vec3 GetMaxBound() const { return m_bound_max; }
        inline glm::vec3 GetMinBound() const { return m_bound_min; }

        inline void SetMaxBound(glm::vec3 max_b) { m_bound_max = max_b; }
        inline void SetMinBound(glm::vec3 min_b) { m_bound_min = min_b; }

        /*VECTOR_FIELD_METHODS(m_vertex_positions, Position, Positions,glm::vec3);
        VECTOR_FIELD_METHODS(m_vertex_normals, Normal, Normals, glm::vec3);
        VECTOR_FIELD_METHODS(m_vertex_colors, Color, Colors, glm::vec3);
        VECTOR_FIELD_METHODS(m_vertex_texcoords, TextureCoord, TextureCoords, glm::vec2);
        VECTOR_FIELD_METHODS(m_indices, Index, Indices, int);*/
        /*inline std::vector<glm::vec3> GetVertices() const { return m_vertices; }
        inline std::vector<glm::vec3> GetNormals() const { return m_normals; }
        inline std::vector<glm::vec3> GetColors() const { return m_colors; }
        inline std::vector<glm::vec2> GetTexCoords() const { return m_texcoords; }

        inline void SetVertices(std::vector<glm::vec3> vertices) { m_vertices = vertices; CalculateBounds(); CenterToPivot(); }
        inline void SetNormals(std::vector<glm::vec3> normals) { m_normals = normals; }
        inline void SetColors(std::vector<glm::vec3> colors) { m_colors = colors; }
        inline void SetTexCoords(std::vector<glm::vec2> texcoords) { m_texcoords = texcoords; }*/

        std::vector<glm::vec3> m_vertex_positions;
        std::vector<glm::vec3> m_vertex_normals;
        std::vector<glm::vec3> m_vertex_colors;
        std::vector<glm::vec2> m_vertex_texcoords;

        std::vector<unsigned int> m_indices;

    private:
        void CenterToPivot();
        void CalculateBounds();

        unsigned int m_face_count = 0;
        unsigned int m_vertex_count = 0;

        glm::vec3 m_bound_max;
        glm::vec3 m_bound_min;
    };
}