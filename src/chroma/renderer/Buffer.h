#pragma once

namespace Chroma
{
    class VertexBuffer
    {
    public:
        //VertexBuffer(const void* data, unsigned int size);
        virtual void Bind() const;
        virtual void Unbind() const;

    private:
        unsigned int m_renderer_id;
    };

    class IndexBuffer
    {
    public:
        //IndexBuffer(const void* data, unsigned int size);
        virtual ~IndexBuffer();

        virtual void Bind() const;
        virtual void Unbind() const;
        virtual void SetBufferData(const unsigned int* data, unsigned int size);

        inline int GetSize() { return m_size; }

    private:
        unsigned int m_renderer_id;
        unsigned int m_size;
    };
}