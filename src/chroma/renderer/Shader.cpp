#pragma once

#include <chroma/renderer/Shader.h>
#include <thirdparty/glad/include/glad/glad.h>
#include <chroma/main/Log.h>
#include <sstream>
#include <fstream>


namespace Chroma
{
    Shader::Shader(const std::string& vertex_shader_data, const std::string& fragment_shader_data, bool read_from_file = false)
    {
        std::string vertex_shader_src;
        std::string fragment_shader_src;
        if (read_from_file)
        {

            std::ifstream vertex_shader_stream(vertex_shader_data, std::ios::in);
            if (vertex_shader_stream.is_open()) 
            {
                std::stringstream sstr;
                sstr << vertex_shader_stream.rdbuf();
                vertex_shader_src = sstr.str();
                vertex_shader_stream.close();
            }
            else 
            {
                CH_ASSERT(false, "Cannot to open vertex shader")
            }

            std::ifstream fragment_shader_stream(fragment_shader_data, std::ios::in);
            if (fragment_shader_stream.is_open()) 
            {
                std::stringstream sstr;
                sstr << fragment_shader_stream.rdbuf();
                fragment_shader_src = sstr.str();
                fragment_shader_stream.close();
            }
            else
            {
                CH_ASSERT(false, "Cannot to open fragment shader")
            }
        }
        else
        {
            vertex_shader_src = vertex_shader_data;
            fragment_shader_src = fragment_shader_data;
        }
        m_renderer_id = glCreateProgram();
        unsigned int vertex_shader = CompileShader(GL_VERTEX_SHADER, vertex_shader_src);
        unsigned int fragment_shader = CompileShader(GL_FRAGMENT_SHADER, fragment_shader_src);

        glAttachShader(m_renderer_id, vertex_shader);
        glAttachShader(m_renderer_id, fragment_shader);
        glLinkProgram(m_renderer_id);
        glValidateProgram(m_renderer_id);


        glDetachShader(m_renderer_id, vertex_shader);
        glDetachShader(m_renderer_id, fragment_shader);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_renderer_id);
    }

    void Shader::Bind() const
    {
        glUseProgram(m_renderer_id);
    }

    void Shader::UnBind() const
    {
        glUseProgram(0);
    }

    unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
    {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            std::stringstream ss;
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);

            ss << "Cannot compile "<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader:\n" << message;
            glDeleteShader(id);

            CH_ASSERT(false, ss.str());
            return -1;
        }

        return id;
    }
}