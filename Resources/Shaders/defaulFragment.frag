#version 430

out vec4 out_color;
in vec3 color;
in vec2 pass_textureCoords;
//uniform vec3 custom_color;

uniform sampler2D textureSampler;

void main()
{
  out_color = texture(textureSampler, pass_textureCoords) * vec4(color, 1.0);
  //out_color = vec4(color, 1.0);
  //out_color = vec4(custom_color, 1.0);
}
