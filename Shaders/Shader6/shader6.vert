#version 420 core

layout(location = 0) in vec3 vPos;
layout(location = 5) in mat4 mv;

uniform mat4 proj;

out vec3 fTex;

void main()
{
    gl_Position = proj*mv*vec4(vPos,0);
    gl_Position = gl_Position.xyww;
    fTex = vPos;
}