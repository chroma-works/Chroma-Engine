#include "OpenGLVertexArrayObject.h"

namespace Chroma
{
    OpenGLVertexArrayObject::OpenGLVertexArrayObject()
    {
        glGenVertexArrays(1, &m_renderer_id);
    }
    OpenGLVertexArrayObject::~OpenGLVertexArrayObject()
    {
        glDeleteVertexArrays(1, &m_renderer_id);
    }
    void OpenGLVertexArrayObject::Bind() const
    {
        glBindVertexArray(m_renderer_id);
    }
    void OpenGLVertexArrayObject::Unbind() const
    {
        glBindVertexArray(0);
    }
    void OpenGLVertexArrayObject::SetVertexBuffer(OpenGLVertexBuffer& vertex_buffer)
    {
        m_vertex_buffer = vertex_buffer;
        CH_ASSERT(vertex_buffer.GetBufferLayout().GetElements().size(), "Buffer has no layout!")

        glBindVertexArray(m_renderer_id);
        vertex_buffer.Bind();

        const auto& layout = vertex_buffer.GetBufferLayout().GetElements();
        for (int i = 0; i < layout.size(); i++)
        {
            glEnableVertexAttribArray(layout[i].shader_index);

            glVertexAttribPointer(layout[i].shader_index,
                GetShaderDataTypeCount(layout[i].data_type),
                ShaderDataTypeToOpenGLBaseType(layout[i].data_type),
                layout[i].normalized,
                vertex_buffer.GetBufferLayout().GetStride(),
                (const void*)layout[i].offset);
        }
    }

    GLenum OpenGLVertexArrayObject::ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case Chroma::ShaderDataType::Float:    return GL_FLOAT;
        case Chroma::ShaderDataType::Float2:   return GL_FLOAT;
        case Chroma::ShaderDataType::Float3:   return GL_FLOAT;
        case Chroma::ShaderDataType::Float4:   return GL_FLOAT;
        case Chroma::ShaderDataType::Mat3:     return GL_FLOAT;
        case Chroma::ShaderDataType::Mat4:     return GL_FLOAT;
        case Chroma::ShaderDataType::Int:      return GL_INT;
        case Chroma::ShaderDataType::Int2:     return GL_INT;
        case Chroma::ShaderDataType::Int3:     return GL_INT;
        case Chroma::ShaderDataType::Int4:     return GL_INT;
        case Chroma::ShaderDataType::Bool:     return GL_BOOL;
        }

        CH_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }
}