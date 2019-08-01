#version 450 core

in float frag_Ldistance;
in vec3 frag_Color;
in vec3 frag_Pos;
in vec2 frag_TexCoord;

uniform sampler2D u_Texture;

out vec4 color;

void main(){
	color = texture(u_Texture, frag_TexCoord);
	//color = frag_Pos;
}