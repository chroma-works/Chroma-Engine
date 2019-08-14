#pragma once

#include <thirdparty/glad/include/glad/glad.h>
#include <chroma/openGL/OpenGLBuffer.h>

namespace Chroma
{
    class OpenGLVertexArrayObject
    {
    public:
        OpenGLVertexArrayObject();
        ~OpenGLVertexArrayObject();

        void Bind() const;
        void Unbind() const;

        void AddVertexBuffer(std::shared_ptr<OpenGLVertexBuffer> vertex_buffer);
        void SetIndexBuffer(std::shared_ptr<OpenGLIndexBuffer> index_buffer);

    private:

        static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type);

        std::vector<std::shared_ptr<OpenGLVertexBuffer>> m_vertex_buffers;
        std::shared_ptr<OpenGLIndexBuffer> m_index_buffer;
        unsigned int m_renderer_id;
    };
}