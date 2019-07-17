#pragma once

#include <chroma/main/Log.h>

namespace Chroma
{

    //From:https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Renderer/Buffer.h
    enum class ShaderDataType
    {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    //From:https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Renderer/Buffer.h
    static uint32_t GetShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float:    return sizeof(float);
        case ShaderDataType::Float2:   return sizeof(float) * 2;
        case ShaderDataType::Float3:   return sizeof(float) * 3;
        case ShaderDataType::Float4:   return sizeof(float) * 4;
        case ShaderDataType::Mat3:     return sizeof(float) * 3 * 3;
        case ShaderDataType::Mat4:     return sizeof(float) * 4 * 4;
        case ShaderDataType::Int:      return sizeof(int);
        case ShaderDataType::Int2:     return sizeof(int) * 2;
        case ShaderDataType::Int3:     return sizeof(int) * 3;
        case ShaderDataType::Int4:     return sizeof(int) * 4;
        case ShaderDataType::Bool:     return sizeof(bool);
        }

        CH_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    static uint32_t GetShaderDataTypeCount(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float:    return 1;
        case ShaderDataType::Float2:   return 2;
        case ShaderDataType::Float3:   return 3;
        case ShaderDataType::Float4:   return 4;
        case ShaderDataType::Int:      return 1;
        case ShaderDataType::Int2:     return 2;
        case ShaderDataType::Int3:     return 3;
        case ShaderDataType::Int4:     return 4;
        case ShaderDataType::Bool:     return 1;
        }

        CH_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    struct VertexAttribute
    {
        std::string shader_var_name;
        unsigned int shader_index;
        unsigned int size;
        unsigned int offset;
        bool normalized;
        ShaderDataType data_type;

        VertexAttribute() = default;
        VertexAttribute(std::string name, unsigned int index, ShaderDataType data_type,
            bool normalized = false, unsigned int offset = 0)
            :shader_var_name(name), shader_index(index), data_type(data_type), size(GetShaderDataTypeSize(data_type)),
            normalized(normalized), offset(offset)
        {}

        VertexAttribute(const VertexAttribute&) = default;
        VertexAttribute& operator = (const VertexAttribute&) = default;
    };

    class VertexBufferLayout
    {
    public:
        VertexBufferLayout() {};
        ~VertexBufferLayout() = default;

        void PushAttribute(VertexAttribute attribute)
        {
            m_attributes.push_back(attribute);

            unsigned int offset = 0;
            m_stride = 0;
            for (int i = 0; i < m_attributes.size(); i++)
            {
                m_attributes[i].offset = offset;
                offset += m_attributes[i].size;

                m_stride += m_attributes[i].size;
            }
        }

        inline unsigned int GetStride() const { return m_stride; }
        inline const std::vector<VertexAttribute>& GetElements() const { return m_attributes; }

    private:
        std::vector<VertexAttribute> m_attributes;
        unsigned int m_stride = 0;
    };

    class Buffer
    {
    public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

    protected:
        unsigned int m_renderer_id;
    };

    class VertexBuffer : public Buffer
    {
    public:
        //VertexBuffer(const void* vertices, unsigned int size);
        ~VertexBuffer() = default;

        inline VertexBufferLayout& GetBufferLayout() { return m_buffer_layout; }
        inline void SetBufferLayout(VertexBufferLayout& layout) { m_buffer_layout = layout; }

    private:
        VertexBufferLayout m_buffer_layout;
    };

    class IndexBuffer : public Buffer
    {
    public:
        //IndexBuffer(uint32_t* indices, unsigned int size);
        ~IndexBuffer() = default;
        inline unsigned int GetSize() { return m_size; }

    protected:
        unsigned int m_size;

    };
}