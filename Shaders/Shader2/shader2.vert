#version 420 core
layout (location=0) in vec3 aPos;
layout (location=5) in mat4 mv;

uniform mat4 proj;

void main()
{
    gl_Position = proj*mv*vec4(aPos,1.f);
}