#version 450 core 
//#shader vertex

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_TexCoord;

uniform mat4 u_Model, u_View, u_Proj;
uniform vec4 u_LightPosition;

/*out vec2 fragTexCoord;
out vec3 fragpos, fragnormal;
out float ldistance;*/

void main()
{
	mat4 u_MVP = u_Proj * u_View * u_Model;
	//ldistance = distance(u_LightPosition.xyz, in_Position);


	vec3 pos = (u_MVP * vec4(in_Position.xyz, 1.0f)).xyz;

	/*fragpos = pos;
	fragnormal = in_Normal;*/

	gl_Position = u_MVP * vec4(in_Position.xyz, 1.0f) ;
	//fragTexCoord = in_TexCoord;
};
