#version 430

out vec4 out_color;
uniform vec3 mycolor;

void main()
{
  //color = vec4(theColor, 1.0);
  out_color = vec4(mycolor, 1.0);//vec4(1.0, 0.0, 0.0, 1.0);
}
