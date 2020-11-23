#version 420 core

in vec3 fColor;
in vec2 fTex;
out vec4 fragColor;

void main()
{
    fragColor = vec4(fTex,0,1);
}