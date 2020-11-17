#version 420 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNorm;
layout(location = 2) in vec2 vTex;
layout(location = 3) in vec3 vParX;
layout(location = 3) in vec3 vParY;

uniform mat4 mvp;

out vec3 fNorm;
out vec2 fTex;
out vec3 fParX;
out vec3 fParY;

void main()
{
    gl_Position = mvp*vec4(vPos,1);

    fNorm = (vec4(vNorm,1)).xyz;
    fParX = (vec4(vParX,1)).xyz;
    fParY = (vec4(vParY,1)).xyz;

    fTex = vTex;
}