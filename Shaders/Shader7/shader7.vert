#version 420 core
layout(location=0) in vec3 vPos;
layout(location=1) in vec3 vColor;
layout(location=5) in mat4 mv;

uniform mat4 proj;

out vec3 fColor;

void main()
{
    gl_Position = proj*(mv*vec4(vPos,0)*0.1+vec4(0.3,0.3,0,0));
    gl_Position.w = 1;
    fColor = vColor;
}