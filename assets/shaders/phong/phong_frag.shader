#version 450 core

struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

in float frag_Ldistance;
//in vec3 frag_Color;
in vec3 frag_Pos;
in vec3 frag_Normal;
in vec2 frag_TexCoord;

uniform Material u_Material;
uniform vec4 u_LightPosition;
uniform mat4 u_Model;
uniform sampler2D u_Texture;

out vec4 color;

void main(){
	// Transform vertex normal into eye coordinates
	vec3 N = normalize(frag_Normal);
    float lDistance = distance(u_LightPosition.xyz, frag_Pos);
    vec3 L = normalize(vec3(u_LightPosition) - frag_Pos);

	// vector from vertex position to light source
    float lambertian = max(dot(L, N), 0.0);
    float specular = 0.0;
    if (lambertian > 0.0) {
        vec3 R = reflect(-L, N);      // Reflected light vector
        vec3 V = normalize(-frag_Pos); // Vector to viewer
        // Compute the specular term
        float specAngle = max(dot(R, V), 0.0);
        specular = pow(specAngle, u_Material.shininess);
    }

	// Because the eye point the is at the orgin
	// the vector from the vertex position to the eye is

	vec3 E = normalize(frag_Pos);

    float fatt = 1.0 / (1.0 + 0.1 * lDistance + 0.01 * lDistance * lDistance);
	vec4 fColor;
    float Ka = u_Material.ambient.w;
    float Kd = u_Material.diffuse.w;
    float Ks = u_Material.specular.w;

	fColor = vec4(Ka * u_Material.ambient.xyz +
            fatt * (Kd * lambertian * u_Material.diffuse.xyz +
                    Ks * specular * u_Material.specular.xyz), 1.0f);
	vec4 gamma = vec4(1.0 / 1.5);
	fColor = pow(fColor, gamma);
	fColor.a = 1.0;
	color = fColor * texture(u_Texture, frag_TexCoord);
}