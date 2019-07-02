#pragma once

namespace Chroma
{
    class Buffer
    {
    public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

    protected:
        unsigned int m_renderer_id;
    };
}