#version 430

in layout(location=0) vec3 position;
//in layout(location=1) vec3 vertexColor;

// TODO: investigate layout binding
//layout(binding = 0) uniform sampler2D DiffuseTexture;
uniform mat4 MVP;

void main()
{
  gl_Position = MVP * vec4(position, 1.0);
  //color = vertexColor;
}
