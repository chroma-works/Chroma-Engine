#include "OpenGLBuffer.h"

namespace Chroma
{
    OpenGLVertexBuffer::OpenGLVertexBuffer()
    {
        glGenBuffers(1, &m_renderer_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
    }
    OpenGLVertexBuffer::OpenGLVertexBuffer(const void* vertices, unsigned int size)
    {
        glGenBuffers(1, &m_renderer_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }
    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_renderer_id);
    }
    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
    }
    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    void OpenGLVertexBuffer::SetBufferStorage(const void* data, unsigned int size)
    {
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }
    void OpenGLVertexBuffer::SetBufferSubData(const void * data, long long int offset, unsigned int size)
    {
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    }
    void OpenGLVertexBuffer::ClearBufferData(const void * data = nullptr)
    {
        glClearBufferData(GL_ARRAY_BUFFER, GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT, &data);
    }

    void OpenGLVertexBuffer::ClearBufferSubData(const void * data, long long int offset, unsigned int size)
    {
        glClearBufferSubData(GL_ARRAY_BUFFER, GL_R32UI, offset, size, GL_RED_INTEGER, GL_UNSIGNED_INT, &data);

    }

    void OpenGLVertexBuffer::CopyBufferSubData(const OpenGLVertexBuffer & read_target, long long int read_offset, long long int write_offset, unsigned int size)
    {
        read_target.Bind();
        Bind();
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, read_offset, write_offset, size);
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer()
    {
        m_size = 0;
        glGenBuffers(1, &m_renderer_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
    }
    OpenGLIndexBuffer::OpenGLIndexBuffer(const void* indices, unsigned int size)
    {
        m_size = size;
        glGenBuffers(1, &m_renderer_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    }
    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_renderer_id);
    }
    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
    }
    void OpenGLIndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    void OpenGLIndexBuffer::SetBufferStorage(const void* data, unsigned int size)
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }
    void OpenGLIndexBuffer::SetBufferSubData(const void * data, long long int offset, unsigned int size)
    {
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
    }
    void OpenGLIndexBuffer::ClearBufferData(const void * data = nullptr)
    {
        glClearBufferData(GL_ELEMENT_ARRAY_BUFFER, GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT, &data);
    }

    void OpenGLIndexBuffer::ClearBufferSubData(const void * data, long long int offset, unsigned int size)
    {
        glClearBufferSubData(GL_ELEMENT_ARRAY_BUFFER, GL_R32UI, offset, size, GL_RED_INTEGER, GL_UNSIGNED_INT, &data);

    }

    void OpenGLIndexBuffer::CopyBufferSubData(const OpenGLIndexBuffer & read_target, long long int read_offset, long long int write_offset, unsigned int size)
    {
        read_target.Bind();
        Bind();
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, read_offset, write_offset, size);
    }
   
}
