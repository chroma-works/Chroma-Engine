#pragma once

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
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float shininess;

        Material(std::string name, glm::vec3 ambi, glm::vec3 diff, glm::vec3 spec, float shin)
            :shader_var_name(name), ambient(ambi), diffuse(diff), specular(spec), shininess(shin) {}

        Material() 
            :shader_var_name("u_Material"), ambient(glm::vec3(1.0f, 1.0f, 1.0f)),
                diffuse(glm::vec3(1.0f, 1.0f, 1.0f)), specular(glm::vec3(1.0f)), shininess(60.0f)
        {}

    };

    class Shader
    {
    public:
        //Default uniform names for auto generated/loaded shaders
        static const std::string MODEL_SH;
        static const std::string VIEW_SH;
        static const std::string PROJ_SH;
        static const std::string NORM_MAT_SH;
        static const std::string CAM_POS_SH;
        static const std::string MATERIAL_SH;

        //Default Layouts for auto generated/loaded shaders
        static const unsigned int POS_LAY = 0;
        static const unsigned int NORM_LAY = 1;
        static const unsigned int TEXC_LAY = 2;

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
        void AddLight(std::shared_ptr<DirectionalLight> lig);
		void AddLight(std::shared_ptr<PointLight> lig);
		void AddLight(std::shared_ptr<SpotLight> lig);
        void UpdateUniforms();

        //Apply RULE OF THREE
        //Delete the copy constructor/assignment.
        Shader(const Shader &) = delete;
        Shader &operator=(const Shader &) = delete;

        Shader(Shader &&other)
        {
            m_renderer_id = other.m_renderer_id;
            other.m_renderer_id = 0;
            m_uniforms = other.m_uniforms;
            num_dir_lights = other.num_dir_lights;
            num_spot_lights = other.num_spot_lights;
            num_point_lights = other.num_point_lights;
        }

        Shader& operator=(Shader &&other)
        {
            if (this != &other)
            {
                Unbind();
                std::swap(m_renderer_id, other.m_renderer_id);
                std::swap(m_uniforms, other.m_uniforms);
                std::swap(num_dir_lights, other.num_dir_lights);
                std::swap(num_spot_lights, other.num_spot_lights);
                std::swap(num_point_lights, other.num_point_lights);
            }
        }

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
        int num_dir_lights = 0;
        int num_point_lights = 0;
        int num_spot_lights = 0;
    };
}