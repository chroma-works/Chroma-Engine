
#version 450 core

in float frag_Ldistance;
in vec3 frag_Color;
in vec3 frag_Pos;

out vec3 color;
void main(){
	color = frag_Color;
	//color = frag_Pos;
}