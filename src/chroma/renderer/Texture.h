#pragma once
#include <string>

class Texture
{
public:
    Texture(const std::string& path, const std::string& uniform_name);
    Texture(const Texture& other);
    Texture &operator=(Texture rhs);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    int inline GetWidth() const { return m_width; }
    int inline GetHeigth() const { return m_heigth; }
    std::string inline GetUniformName() const { return m_uniform_name; }
private:
    unsigned int m_rendererID;
    std::string m_filepath;
    unsigned char* m_localbuffer;
    int m_width, m_heigth, m_BPP;
    std::string m_uniform_name;
};