#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoord;

out vec2 TexCoord;

void main()
{
    gl_Position = position;
    vec2 newTCoord = texCoord;
    newTCoord.y = 1.0 - newTCoord.y;
    TexCoord = newTCoord;
}