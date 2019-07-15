
#version 330 core
in vec3 fragmentColor;
out vec3 color;
uniform vec3 testcolor = vec3(1,0,1);
void main(){
  //color = fragmentColor;
  color = testcolor;
}