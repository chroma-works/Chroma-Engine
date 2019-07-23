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
    void OpenGLVertexArrayObject::AddVertexBuffer(OpenGLVertexBuffer* vertex_buffer)
    {
        CH_ASSERT(vertex_buffer->GetBufferLayout().GetElements().size(), "Buffer has no layout!");

        Bind();
        vertex_buffer->Bind();

        m_vertex_buffers.push_back(vertex_buffer);

        const auto& layout = vertex_buffer->GetBufferLayout().GetElements();
        for (VertexAttribute element : layout)
        {
            glVertexAttribPointer(element.shader_layout_index,
                GetShaderDataTypeCount(element.data_type),
                ShaderDataTypeToOpenGLBaseType(element.data_type),
                element.normalized,
                vertex_buffer->GetBufferLayout().GetStride(),
                (const void*)element.offset);

            glEnableVertexAttribArray(element.shader_layout_index);
        }
        Unbind();
    }

    void OpenGLVertexArrayObject::SetIndexBuffer(OpenGLIndexBuffer* index_buffer)
    {
        Bind();
        index_buffer->Bind();

        m_index_buffer = index_buffer;
        Unbind();
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