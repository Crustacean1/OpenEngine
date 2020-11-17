#version 420

out vec4 rColor;

in vec3 c1;

void main()
{
    rColor = vec4(c1,1);
}