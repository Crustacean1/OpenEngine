#version 420 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 vTex;

uniform mat4 mvp;

out vec3 fColor;
out vec2 fTex;

void main()
{
    fColor = aColor;
    fTex = vTex;
    gl_Position = mvp*vec4(aPos,1);
}