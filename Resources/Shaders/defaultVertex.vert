#version 430

in layout(location=0) vec3 position;
in layout(location=1) vec3 normal;
in layout(location=2) vec3 vertexColor;
in layout(location=3) vec2 textureCoords;

out vec3 color;
out vec2 pass_textureCoords;
// TODO: investigate layout binding
//layout(binding = 0) uniform sampler2D DiffuseTexture;
uniform mat4 MVP;

void main()
{
  gl_Position = MVP * vec4(position, 1.0);
  pass_textureCoords = textureCoords;
  color = vertexColor;
}
