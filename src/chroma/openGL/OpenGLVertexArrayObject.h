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

        void AddVertexBuffer(OpenGLVertexBuffer* vertex_buffer);
        void SetIndexBuffer(OpenGLIndexBuffer* index_buffer);

    private:

        static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type);

        std::vector<OpenGLVertexBuffer*> m_vertex_buffers;
        OpenGLIndexBuffer* m_index_buffer;
        unsigned int m_renderer_id;
    };
}