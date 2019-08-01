#pragma once

#include <string>
#include <thirdparty/glad/include/glad/glad.h>

class Texture
{
public:
    enum TextureWrap{ EDGE_CLAMP = GL_CLAMP_TO_EDGE, MIRRORED_REPEAT = GL_MIRRORED_REPEAT, REPEAT = GL_REPEAT};

    Texture(const std::string& path, TextureWrap wrap = EDGE_CLAMP);
    Texture(const Texture& other);
    Texture &operator=(Texture rhs);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    int inline GetWidth() const { return m_width; }
    int inline GetHeigth() const { return m_heigth; }
private:
    unsigned int m_rendererID;
    std::string m_filepath;
    unsigned char* m_localbuffer;
    int m_width, m_heigth, m_BPP;
    TextureWrap m_t_wrap;
};