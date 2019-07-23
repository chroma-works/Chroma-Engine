#version 430 core
layout(location = 0) in vec4 in_Position;
layout(location = 1) in vec3 in_Color;
out vec3 fragmentColor;

uniform mat4 u_Model, u_View, u_Proj;

void main(){
	  mat4 u_MVP = u_Proj * u_View * u_Model;
	  gl_Position = u_MVP * in_Position;
	  fragmentColor = in_Color;
}