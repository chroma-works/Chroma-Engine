#version 330 core
layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec3 vertexColor;
out vec3 fragmentColor;

uniform mat4 u_Model, u_View, u_Proj;

void main(){
	  mat4 u_MVP = u_Proj * u_View * u_Model;
	  gl_Position = u_MVP * vertexPosition;
	  fragmentColor = vertexColor;
}