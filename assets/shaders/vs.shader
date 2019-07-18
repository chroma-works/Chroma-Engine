#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
out vec3 fragmentColor;

uniform mat4 u_Model;

void main(){
  vec4 vertexPosition = vec4(vertexPosition_modelspace.xyz, 1.0);
  gl_Position = u_Model * vertexPosition;
  gl_Position.w = 1.0;
  fragmentColor = vertexColor;
}