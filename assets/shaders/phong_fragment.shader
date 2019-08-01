
#shader fragment
#version 430 core

struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

layout(location = 0) out vec4 color;

in vec2 fragTexCoord;
in vec3 fragpos, fragnormal;
in float ldistance;
//layout(location = 1) in vec3 normal;

uniform Material u_Material;
//uniform mat4 u_NormalMat;
uniform sampler2D u_Texture;
uniform vec4 u_LightPosition;
uniform mat4 u_Model;

void main()
{
	// Transform vertex normal into eye coordinates
	vec3 N = normalize(mat3(transpose(inverse(u_Model))) * fragnormal);

	// vector from vertex position to light source
	// check for directional light
	vec3 L;
	if (u_LightPosition.w == 0.0)
		L = normalize(u_LightPosition.xyz);
	else
		L = normalize(u_LightPosition.xyz - fragpos);

	// Because the eye point the is at the orgin
	// the vector from the vertex position to the eye is

	vec3 E = normalize(fragpos);

	float fatt = 1.0 / (1 + 0.00001f * ldistance + 0.00001f * ldistance * ldistance);
	vec4 fColor;

	vec3 H = normalize(L + E);
	vec4 ambient = u_Material.ambient;

	float Kd = max(dot(L, N), 0.0);
	vec4  diffuse = Kd * u_Material.diffuse;

	float Ks = 0.0f;
	Ks = pow(max(dot(N, H), 0.0), u_Material.shininess);
	vec4  specular = Ks * u_Material.specular ;

	if (dot(L, N) < 0.0) specular = vec4(0.0, 0.0, 0.0, 1.0);

	fColor = ambient + fatt * (diffuse + specular);
	vec4 gamma = vec4(1.0 / 2.1);
	fColor = pow(fColor, gamma);
	fColor.a = 1.0;
	color = fColor * texture(u_Texture, fragTexCoord);
};