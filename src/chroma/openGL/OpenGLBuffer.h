#pragma once

#include <chroma/renderer/Buffer.h>
#include <thirdparty/glad/include/glad/glad.h>

namespace Chroma
{
    class OpenGLVertexBuffer : public Buffer
    {
    public:
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

    private:
    };
}
