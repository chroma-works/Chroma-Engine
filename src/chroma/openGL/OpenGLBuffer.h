#pragma once

#include <chroma/renderer/Buffer.h>
#include <thirdparty/glad/include/glad/glad.h>

namespace Chroma
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer();
        OpenGLVertexBuffer(const void* vertices, unsigned int size);
        ~OpenGLVertexBuffer();

        void Bind() const override;
        void Unbind() const override;

        void SetBufferStorage(const void* data, unsigned int size);
        void SetBufferSubData(const void* data, long long int offset, unsigned int size);

        void ClearBufferData(const void * data);
        void ClearBufferSubData(const void* data, long long int offset, unsigned int size);

        void CopyBufferSubData(const OpenGLVertexBuffer& read_target, long long int readOffset, long long int writeOffset, unsigned int size);

        /*void* MapBuffer();
        void UnmapBuffer();*/

        //Apply RULE OF THREE
        //Delete the copy constructor/assignment.
        OpenGLVertexBuffer(const OpenGLVertexBuffer &) = delete;
        OpenGLVertexBuffer &operator=(const OpenGLVertexBuffer &) = delete;

        OpenGLVertexBuffer(OpenGLVertexBuffer &&other)
        {
            m_renderer_id = other.m_renderer_id;
            other.m_renderer_id = 0;
        }

        OpenGLVertexBuffer &operator=(OpenGLVertexBuffer &&other)
        {
            if (this != &other)
            {
                Unbind();
                std::swap(m_renderer_id, other.m_renderer_id);
            }
        }

    };


    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer();
        OpenGLIndexBuffer(const void* vertices, unsigned int size);
        ~OpenGLIndexBuffer();

        void Bind() const override;
        void Unbind() const override;

        void SetBufferStorage(const void* data, unsigned int size);
        void SetBufferSubData(const void* data, long long int offset, unsigned int size);

        void ClearBufferData(const void * data);
        void ClearBufferSubData(const void* data, long long int offset, unsigned int size);

        void CopyBufferSubData(const OpenGLIndexBuffer& read_target, long long int readOffset, long long int writeOffset, unsigned int size);

        /*void* MapBuffer();
        void UnmapBuffer();*/

        //Apply RULE OF THREE
        //Delete the copy constructor/assignment.
        OpenGLIndexBuffer(const OpenGLIndexBuffer &) = delete;
        OpenGLIndexBuffer &operator=(const OpenGLIndexBuffer &) = delete;

        OpenGLIndexBuffer(OpenGLIndexBuffer &&other)
        {
            m_renderer_id = other.m_renderer_id;
            other.m_renderer_id = 0;
        }

        OpenGLIndexBuffer &operator=(OpenGLIndexBuffer &&other)
        {
            if (this != &other)
            {
                Unbind();
                std::swap(m_renderer_id, other.m_renderer_id);
            }
        }
    };
}
