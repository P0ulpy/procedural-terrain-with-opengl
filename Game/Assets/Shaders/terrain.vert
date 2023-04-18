#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoord;
out vec3 Normal;
out float Height;

uniform mat4 model;

void main()
{
    gl_Position = model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
    Normal = aNormal;
    Height = aPos.y;
}
