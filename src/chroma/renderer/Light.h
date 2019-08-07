#pragma once
#include <thirdparty/glm/glm/glm.hpp>

namespace Chroma
{
    struct DirectionalLight {
        std::string shader_var_name =  "u_DirLights";
        
        glm::vec3* direction;

        glm::vec3* ambient;
        glm::vec3* diffuse;
        glm::vec3* specular;

        DirectionalLight(glm::vec3* dir, glm::vec3* amb,
            glm::vec3* diff, glm::vec3* spec, std::string name = "u_DirLights")
        : direction(dir), ambient(amb), diffuse(diff), specular(spec), shader_var_name(name)
        {}
    };

    struct PointLight {
        std::string shader_var_name = "u_PointLights";

        glm::vec3* position;
		//this might need direction here

        float constant;
        float linear;
        float quadratic;

        glm::vec3* ambient;
        glm::vec3* diffuse;
        glm::vec3* specular;

        PointLight(glm::vec3* pos, glm::vec3* amb,
            glm::vec3* diff, glm::vec3* spec, float cons = 1.0f, float lin = 0.01f, float quad = 0.0001f, 
			std::string name = "u_PointLights")
            : position(pos), ambient(amb), diffuse(diff), specular(spec), constant(cons), linear(lin), quadratic(quad), 
			shader_var_name(name)
        {}
    };

    struct SpotLight {
        std::string shader_var_name = "u_SpotLights";

        glm::vec3* position;
        glm::vec3* direction;
        float cutOff;
        float outerCutOff;

        float constant;
        float linear;
        float quadratic;

        glm::vec3* ambient;
        glm::vec3* diffuse;
        glm::vec3* specular;

        SpotLight(glm::vec3* pos, glm::vec3* dir, glm::vec3* amb,
            glm::vec3* diff, glm::vec3* spec, float cons = 1.0f, float lin = 0.03f, float quad = 0.0009f, 
			float cut = 12.5f, float outerCut = 15.0f, std::string name = "u_SpotLights")
            : position(pos), direction(dir), ambient(amb), diffuse(diff), specular(spec), constant(cons), linear(lin), quadratic(quad), 
			cutOff(cut), outerCutOff(outerCut), shader_var_name(name)
        {}
    };
}