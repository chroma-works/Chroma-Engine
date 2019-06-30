#pragma once
#include <stdio.h>
#include <string>

namespace Chroma
{
    class Shader
    {
    public:
        static const bool READ_FILE_PATH = true;
        Shader(const std::string& vertex_shader, const std::string& fragment_shader, bool read_from_file);
        ~Shader();

        void Bind() const;
        void UnBind() const;

    private:
        unsigned int CompileShader(unsigned int type, const std::string & source);
        uint32_t m_renderer_id;
    };
}