#version 450 core

precision highp float;
layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_TexCoord;

uniform mat4 u_Model, u_View, u_Proj, u_NormalMat;

out vec2 frag_TexCoord;
out vec3 frag_Normal, frag_Pos;

void main(){

    vec4 vertPos4 =  u_Model * vec4(in_Position, 1.0);
    frag_Pos = vec3(vertPos4) / vertPos4.w;
    frag_Normal = vec3(u_NormalMat * vec4(in_Normal, 0.0));
    gl_Position = u_Proj * u_View * u_Model  * vec4(in_Position, 1.0);

    frag_TexCoord = in_TexCoord;
}