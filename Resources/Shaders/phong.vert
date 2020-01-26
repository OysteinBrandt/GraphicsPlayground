#version 430 core

in layout (location = 0) vec3 aPos;
in layout (location = 1) vec3 aNormal;
in layout (location = 2) vec3 aColor;
in layout (location = 3) vec2 textureCoords;

out vec3 FragPos;
out vec3 Normal;
out vec3 Color;
out vec2 TextureCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    Color = aColor;
    TextureCoords = textureCoords;
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}