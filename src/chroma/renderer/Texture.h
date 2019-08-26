#pragma once

#include <string>

namespace Chroma
{
    class Texture
    {
    public:
        enum TextureWrap{ EDGE_CLAMP = 0x812F, MIRRORED_REPEAT = 0x8370, REPEAT = 0x2901};

        Texture();
        Texture(const std::string& path, TextureWrap wrap = EDGE_CLAMP);
        Texture(const Texture& other);
        Texture &operator=(Texture rhs);
        ~Texture();

        void Bind(unsigned int slot = 0) const;
        void Unbind() const;

        int inline GetWidth() const { return m_width; }
        int inline GetHeigth() const { return m_heigth; }

    private:
        unsigned int m_renderer_id;
        std::string m_filepath;
        unsigned char* m_localbuffer;
        int m_width, m_heigth, m_BPP;
        TextureWrap m_t_wrap;
    };
}