#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <thirdparty/stb_image/stb_image.h>

Texture::Texture(const std::string & path, TextureWrap wrap)
    : m_rendererID(0), m_filepath(path), m_localbuffer(nullptr), m_width(0), m_heigth(0), m_BPP(0), m_t_wrap(wrap)
{
    stbi_set_flip_vertically_on_load(false);
    m_localbuffer = stbi_load(path.c_str(), &m_width, &m_heigth, &m_BPP, 4);

    glGenTextures(1, &m_rendererID);
    glBindTexture(GL_TEXTURE_2D, m_rendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_heigth, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localbuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (m_localbuffer)
        stbi_image_free(m_localbuffer);
}

Texture& Texture::operator=(Texture rhs)
{
    if (this != &rhs)
    {
        m_BPP = rhs.m_BPP;
        m_filepath = rhs.m_filepath;
        m_heigth = rhs.m_heigth;
        //m_localbuffer = nullptr;
        m_rendererID = rhs.m_rendererID;
        //m_uniform_name = rhs.m_uniform_name;
        m_width = rhs.m_width;
        m_t_wrap = rhs.m_t_wrap;

        stbi_set_flip_vertically_on_load(false);
        m_localbuffer = stbi_load(m_filepath.c_str(), &m_width, &m_heigth, &m_BPP, 4);

        glGenTextures(1, &m_rendererID);
        glBindTexture(GL_TEXTURE_2D, m_rendererID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, rhs.m_t_wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, rhs.m_t_wrap);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_heigth, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localbuffer);
        glBindTexture(GL_TEXTURE_2D, 0);

        if (m_localbuffer)
            stbi_image_free(m_localbuffer);

    }
    return *this;
}

Texture::Texture(const Texture & other)
    :m_rendererID(other.m_rendererID),
    m_filepath(other.m_filepath),
    //m_localbuffer(other.m_localbuffer),
    m_width(other.m_width),
    m_heigth(other.m_heigth),
    m_BPP(other.m_BPP),
    m_t_wrap(other.m_t_wrap)/*,
    m_uniform_name(other.m_uniform_name)*/
{
    stbi_set_flip_vertically_on_load(false);
    m_localbuffer = stbi_load(m_filepath.c_str(), &m_width, &m_heigth, &m_BPP, 4);

    glGenTextures(1, &m_rendererID);
    glBindTexture(GL_TEXTURE_2D, m_rendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, other.m_t_wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, other.m_t_wrap);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_heigth, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localbuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (m_localbuffer)
        stbi_image_free(m_localbuffer);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_rendererID);
}

void Texture::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_rendererID);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}