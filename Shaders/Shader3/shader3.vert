#version 420 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform mat4 mvp;

out vec3 fColor;

void main()
{
    fColor = aColor;
    gl_Position = mvp*vec4(aPos,1);
}