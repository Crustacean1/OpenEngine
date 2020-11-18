#version 420 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNorm;
layout(location = 2) in vec2 vTex;
layout(location = 3) in vec3 vParX;
layout(location = 3) in vec3 vParY;

uniform mat4 mvp;
uniform mat4 mv;

out vec3 fPos;
out vec3 fNorm;
out vec2 fTex;
out vec3 fParX;
out vec3 fParY;

void main()
{
    gl_Position = mvp*vec4(vPos,1);

    fPos = (mv*vec4(vPos,1)).xyz;
    fNorm = (mvp*vec4(vNorm,0)).xyz;
    fParX = (mvp*vec4(vParX,0)).xyz;
    fParY = (mvp*vec4(vParY,0)).xyz;

    fTex = vTex;
}