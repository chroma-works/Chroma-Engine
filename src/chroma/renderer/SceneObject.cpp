#include "SceneObject.h"
#include <thirdparty/glm/glm/gtc/matrix_transform.hpp>
#include <thirdparty/glm/glm/gtx/quaternion.hpp>

namespace Chroma
{
    SceneObject::SceneObject(Mesh mesh, std::string name, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
        : m_mesh(mesh), m_name(name), m_position(pos), m_rotation(glm::quat(rot)), m_scale(scale)
    {
        m_texture = Texture("../assets/textures/white.png");//Set texture to white to avoid all black shaded objects

        //Vertex positions buffer
        std::shared_ptr<OpenGLVertexBuffer> position_buffer = std::make_shared<OpenGLVertexBuffer>((void*)m_mesh.m_vertex_positions.data(),
            m_mesh.m_vertex_positions.size() * sizeof(GLfloat) * 3);

        VertexAttribute layout_attribute("in_Position", Shader::POS_LAY, ShaderDataType::Float3, GL_FALSE);
        VertexBufferLayout vertex_buffer_layout;
        vertex_buffer_layout.PushAttribute(layout_attribute);
        position_buffer->SetBufferLayout(vertex_buffer_layout);

        m_vertex_buffers.push_back(position_buffer);

        //Vertex normals buffer
        std::shared_ptr<OpenGLVertexBuffer> normal_buffer = std::make_shared<OpenGLVertexBuffer>((void*)m_mesh.m_vertex_normals.data(),
            m_mesh.m_vertex_normals.size() * sizeof(GLfloat) * 3);

        VertexAttribute layout_attribute2("in_Normal", Shader::NORM_LAY, ShaderDataType::Float3, GL_FALSE);
        VertexBufferLayout vertex_buffer_layout2;
        vertex_buffer_layout2.PushAttribute(layout_attribute2);
        normal_buffer->SetBufferLayout(vertex_buffer_layout2);

        m_vertex_buffers.push_back(normal_buffer);

        //Vertex texture coords buffer
        std::shared_ptr<OpenGLVertexBuffer> tex_coord_buffer = std::make_shared<OpenGLVertexBuffer>((void*)m_mesh.m_vertex_texcoords.data(),
            m_mesh.m_vertex_texcoords.size() * sizeof(GLfloat) * 2);

        VertexAttribute layout_attribute3("in_TexCoord", Shader::TEXC_LAY, ShaderDataType::Float2, GL_FALSE);
        VertexBufferLayout vertex_buffer_layout3;
        vertex_buffer_layout3.PushAttribute(layout_attribute3);
        tex_coord_buffer->SetBufferLayout(vertex_buffer_layout3);

        m_vertex_buffers.push_back(tex_coord_buffer);

        //index buffer
        std::shared_ptr<OpenGLIndexBuffer> index_buffer = std::make_shared<OpenGLIndexBuffer>(m_mesh.m_indices.data(), m_mesh.m_indices.size());
        m_index_buffer = index_buffer;

        //vertex array object
        m_vao.AddVertexBuffer(position_buffer);
        m_vao.AddVertexBuffer(normal_buffer);
        m_vao.AddVertexBuffer(tex_coord_buffer);
        m_vao.SetIndexBuffer(index_buffer);
    }

    void SceneObject::Draw(DrawMode mode)
    {
        m_texture.Bind();
        m_vao.Bind();
        glDrawElements(mode, m_index_buffer->GetSize(), GL_UNSIGNED_INT, NULL);
    }

    void SceneObject::RecalculateModelMatrix()
    {
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_position);
        glm::mat4 rotation = glm::toMat4(m_rotation);
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_scale);

        m_model_matrix =  translation * rotation * scale ;
    }
}