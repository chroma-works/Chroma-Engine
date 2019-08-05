#pragma once

#include <thirdparty/glad/include/glad/glad.h>
#include <stdio.h>
#include <string>
#include <chroma/renderer/Buffer.h>
#include <chroma/renderer/Light.h>
#include <thirdparty/glm/glm/glm.hpp>

namespace Chroma
{
    struct Material
    {
        std::string shader_var_name;
        glm::vec4* ambient;
        glm::vec4* diffuse;
        glm::vec4* specular;
        float shininess;

        Material(std::string name, glm::vec4* ambi, glm::vec4* diff, glm::vec4* spec, float shin)
            :shader_var_name(name), ambient(ambi), diffuse(diff), specular(spec), shininess(shin) {}
    };

    class Shader
    {
    public:
        static inline Shader* ReadAndBuildShaderFromFile
        (const std::string& vertex_path, const std::string& fragment_path) 
        {
            return new Shader(vertex_path, fragment_path, READ_FILE_PATH);
        }

        static inline Shader* ReadAndBuildShaderFromSource
        (const std::string& vertex_src, const std::string& fragment_src)
        {
            return new Shader(vertex_src, fragment_src);
        }
        ~Shader();

        void Bind() const;
        void Unbind() const;
        void CreateUniform(std::string name, ShaderDataType type, void* data);
        void CreateUniform(Material* mat);
        void AddLight(DirectionalLight * lig);
        void UpdateUniforms();

    private:
        struct Uniform
        {
            std::string shader_var_name;
            unsigned int shader_location = -1;      //layout location in the shader
            ShaderDataType data_type;
            void* data;

            Uniform(std::string name, ShaderDataType data_type)
                : shader_var_name(name), shader_location(-1), data_type(data_type)
            {}
        };


        static const bool READ_FILE_PATH = true;
        Shader(const std::string& vertex_shader, const std::string& fragment_shader, bool read_from_file = false);
        unsigned int CompileShader(unsigned int type, const std::string & source);
        void AddUniform(Uniform uniform);

        uint32_t m_renderer_id;
        std::vector<Uniform> m_uniforms;
        std::vector<DirectionalLight*> m_dir_lights;
        std::vector<PointLight*> m_point_lights;
        std::vector<SpotLight*> m_spot_lights;
    };
}