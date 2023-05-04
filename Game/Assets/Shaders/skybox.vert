#version 460 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 viewProjection;
uniform mat4 model;

void main()
{
    TexCoords = aPos;
    gl_Position = viewProjection * model * vec4(aPos, 1.0);
}
