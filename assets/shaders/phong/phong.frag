#version 450 core
precision highp float;
//---------------------structs-----------------------------

struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

//----------------------shader------------------------------
#define MAX_NUM_LIGHTS 15

in vec3 frag_Pos;
in vec3 frag_Normal;
in vec2 frag_TexCoord;

uniform int u_NumDirLights;
uniform int u_NumPointLights;
uniform int u_NumSpotLights;

uniform Material u_Material;
uniform vec4 u_LightPosition;
uniform sampler2D u_Texture;
uniform vec3 u_CameraPos;

uniform DirLight u_DirLights[MAX_NUM_LIGHTS];
uniform PointLight u_PointLights[MAX_NUM_LIGHTS];
uniform SpotLight u_SpotLights[MAX_NUM_LIGHTS];

out vec4 color;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main(){

	// Transform vertex normal into eye coordinates
	vec3 N = normalize(frag_Normal);
    vec3 L = normalize(vec3(u_LightPosition) - frag_Pos);
    vec3 V = normalize(u_CameraPos - frag_Pos); 

    vec3 result = vec3(0.0f, 0.0f, 0.0f);
    for(int i = 0; i < u_NumDirLights; i++)
    {
        result += CalcDirLight(u_DirLights[i], N, V);
    }
    for(int i = 0; i < u_NumPointLights; i++)
    {
        result += CalcPointLight(u_PointLights[i], N, frag_Pos, V);
    }
    for(int i = 0; i < u_NumSpotLights; i++)
    {
        result += CalcSpotLight(u_SpotLights[i], N, frag_Pos, V);
    }

	vec4 gamma = vec4(1.0 / 1.5);
	//fColor = pow(fColor, gamma);
	//fColor.a = 1.0;
	color = vec4(result, 1.0f) * texture(u_Texture, frag_TexCoord);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    if (diff > 0.0)
        spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
    // combine results
	return vec3(u_Material.ambient.xyz +
                (diff * u_Material.diffuse.xyz +
                  spec * u_Material.specular.xyz));
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    if (diff > 0.0)
        spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
  
    // combine results
    vec3 ambient = light.ambient * u_Material.ambient.xyz ;
    vec3 diffuse = light.diffuse * diff * vec3(u_Material.diffuse);
    vec3 specular = light.specular * spec * vec3((u_Material.specular));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    if (diff > 0.0)
        spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(u_Material.diffuse);
    vec3 diffuse = light.diffuse * diff * vec3(u_Material.diffuse);
    vec3 specular = light.specular * spec * vec3(u_Material.specular);
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}