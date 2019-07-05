#pragma once
#include <stdio.h>
#include <string>

namespace Chroma
{
    class Shader
    {
    public:
        static inline Shader* ReadAndBuildShaderFromFile
        (const std::string& vertex_path, const std::string& fragment_path) 
        {
            return new Shader(vertex_path, fragment_path, true);
        }

        static inline Shader* ReadAndBuildShaderFromSource
        (const std::string& vertex_src, const std::string& fragment_src)
        {
            return new Shader(vertex_src, fragment_src, false);
        }
        ~Shader();

        void Bind() const;
        void Unbind() const;

    private:
        static const bool READ_FILE_PATH = true;
        Shader(const std::string& vertex_shader, const std::string& fragment_shader, bool read_from_file);
        unsigned int CompileShader(unsigned int type, const std::string & source);
        uint32_t m_renderer_id;
    };
}