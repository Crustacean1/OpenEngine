#version 420 core

in vec3 fColor;
out vec4 rColor;

void main()
{
    rColor = vec4(fColor,1);
}