#version 420 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNorm;
layout(location = 2) in vec2 vTex;
layout(location = 3) in vec3 vParX;
layout(location = 4) in vec3 vParY;

uniform mat4 mvp;

out vec4 gParX;
out vec4 gParY;
out vec4 gNorm;

void main()
{
    gl_Position = mvp*vec4(vPos,1);

    gParX = (mvp*(vec4(vPos+vParX*0.2,1)));
    gParY = (mvp*(vec4(vPos+vParY*0.2,1)));
    gNorm = (mvp*(vec4(vPos+vNorm*0.2,1)));
}