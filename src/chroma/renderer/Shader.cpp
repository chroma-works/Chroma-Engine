#pragma once

#include <chroma/renderer/Shader.h>
#include <chroma/main/Log.h>
#include <sstream>
#include <fstream>
#include <thirdparty/glm/glm/glm.hpp>

namespace Chroma
{
    Shader::Shader(const std::string& vertex_shader_data, const std::string& fragment_shader_data, bool read_from_file)
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

        CH_INFO("Shaders compiled and linked successfully");
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_renderer_id);
    }

    void Shader::Bind() const
    {
        glUseProgram(m_renderer_id);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }

    void Shader::CreateUniform(std::string name, ShaderDataType type, void* data)
    {
        Uniform uniform(name, type);
        uniform.data = data;
        AddUniform(uniform);
    }

    void Shader::CreateUniform(Material mat)
    {
        Uniform ambient(mat.shader_var_name + ".ambient", ShaderDataType::Float4);
        ambient.data = &mat.ambient;
        Uniform diffuse(mat.shader_var_name + ".diffuse", ShaderDataType::Float4);
        diffuse.data = &mat.diffuse;
        Uniform specular(mat.shader_var_name + ".specular", ShaderDataType::Float4);
        specular.data = &mat.specular;
        Uniform shininess(mat.shader_var_name + ".shininess", ShaderDataType::Float);
        shininess.data = &mat.shininess;

        AddUniform(ambient);
        AddUniform(diffuse);
        AddUniform(specular);
        AddUniform(shininess);
    }

    void Shader::UpdateUniforms()
    {
        Bind();
        for (int i = 0; i < m_uniforms.size(); i++)
        {
            Uniform uniform = m_uniforms[i];
            switch (uniform.data_type)
            {
            case ShaderDataType::Bool:
                glUniform1i(uniform.shader_location, **(bool **)&(uniform).data);
                break;
            case ShaderDataType::Float4:
                glUniform4f(uniform.shader_location, (*((float **)&uniform.data))[0],
                    (*((float **)&uniform.data))[1], (*((float **)&uniform.data))[2],
                    (*((float **)&uniform.data))[3]);
                break;
            case ShaderDataType::Float3:
                glUniform3f(uniform.shader_location, (*((float **)&uniform.data))[0],
                    (*((float **)&uniform.data))[1], (*((float **)&uniform.data))[2]);
                break;
            case ShaderDataType::Float2:
                glUniform2f(uniform.shader_location, (*((float **)&uniform.data))[0],
                    (*((float **)&uniform.data))[1]);
                break;
            case ShaderDataType::Float:
                glUniform1f(uniform.shader_location, **(float **)&(uniform).data);
                break;
            case ShaderDataType::Int4:
                glUniform4f(uniform.shader_location, (*((int **)&uniform.data))[0],
                    (*((int **)&uniform.data))[1], (*((int **)&uniform.data))[2],
                    (*((int **)&uniform.data))[3]);
                break;
            case ShaderDataType::Int3:
                glUniform3f(uniform.shader_location, (*((int **)&uniform.data))[0],
                    (*((int **)&uniform.data))[1], (*((int **)&uniform.data))[2]);
                break;
            case ShaderDataType::Int2:
                glUniform2f(uniform.shader_location, (*((int **)&uniform.data))[0],
                    (*((int **)&uniform.data))[1]);
                break;
            case ShaderDataType::Int:
                glUniform1f(uniform.shader_location, **(int **)&(uniform).data);
                break;
            case ShaderDataType::Mat3:
                glUniformMatrix3fv(uniform.shader_location, 1, GL_FALSE,  (((float **)&uniform.data))[0]);
                break;
            case ShaderDataType::Mat4:
                glUniformMatrix4fv(uniform.shader_location, 1, GL_FALSE, (((float **)&uniform.data))[0]);
                break;
            default:
                CH_ERROR("Unknown type!");
            }
        }
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

    void Shader::AddUniform(Uniform uniform)
    {
        for (int i = 0; i < m_uniforms.size(); i++)
        {
            if (uniform.shader_var_name.compare(m_uniforms[i].shader_var_name) == 0)
            {
                CH_WARN("Uniform " + uniform.shader_var_name + " is already added");
                return;
            }
        }
        int location = glGetUniformLocation(m_renderer_id, uniform.shader_var_name.c_str());
        if (location == -1)
            CH_WARN("Uniform " + uniform.shader_var_name + " does not exist!");
        else
        {
            uniform.shader_location = location;
            m_uniforms.push_back(uniform);
        }
    }
}