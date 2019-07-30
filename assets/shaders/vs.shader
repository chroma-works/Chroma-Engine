#version 450 core
layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Color;
out vec3 fragmentColor;

uniform mat4 u_Model, u_View, u_Proj;

void main(){
	  mat4 u_MVP = u_Proj * u_View * u_Model;
	  gl_Position = u_MVP * vec4(in_Position.xyz, 1.0f);
	  //fragmentColor = in_Color;
	  fragmentColor = vec3(0.0f, 0.0f, 1.0f);
}