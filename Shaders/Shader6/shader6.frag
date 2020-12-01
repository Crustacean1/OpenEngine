#version 420 core

in vec3 fTex;
out vec4 rColor;

uniform samplerCube cubemap;

void main()
{
    rColor = texture(cubemap,fTex);
}