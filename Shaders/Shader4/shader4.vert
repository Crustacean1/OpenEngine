#version 420 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNorm;
layout(location = 2) in vec2 vTex;
layout(location = 3) in vec3 vParX;
layout(location = 4) in vec3 vParY;
layout(location = 5) in mat4 mv;

uniform mat4 proj;

out vec3 fPos;
out vec3 fNorm;
out vec2 fTex;
out vec3 fParX;
out vec3 fParY;

void main()
{
    gl_Position = proj*mv*vec4(vPos,1);

    fPos = (mv*vec4(vPos,1)).xyz;
    fNorm = (mv*vec4(vNorm,0)).xyz;
    fParX = (mv*vec4(vParX,0)).xyz;
    fParY = (mv*vec4(vParY,0)).xyz;

    fTex = vTex;
}