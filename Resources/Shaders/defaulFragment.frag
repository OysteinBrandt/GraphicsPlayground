#version 430

out vec4 out_color;
in vec3 color;
//uniform vec3 custom_color;

void main()
{
  out_color = vec4(color, 1.0);
  //out_color = vec4(custom_color, 1.0);
}
