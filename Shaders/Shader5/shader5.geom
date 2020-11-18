#version 420 core
layout(triangles) in;
layout(line_strip,max_vertices=6) out;

in vec4 gParX[];
in vec4 gParY[];
in vec4 gNorm[];

out vec3 c1;

void drawNormalSpace(int i)
{
    gl_Position = gl_in[i].gl_Position;
    c1 = vec3(0,0.4,0.5);
    EmitVertex();
    gl_Position = gParX[i];
    c1 = vec3(1,1,1);
    EmitVertex();

    /*gl_Position = gl_in[i].gl_Position;
    c1 = vec3(0.7,0.1,0);
    EmitVertex();
    gl_Position = gParY[i];
    c1 = vec3(1,1,1);
    EmitVertex();
    EndPrimitive();

    gl_Position = gl_in[i].gl_Position;
    c1 = vec3(0.1,0.7,0);
    EmitVertex();
    gl_Position = gNorm[i];
    c1 = vec3(1,1,1);
    EmitVertex();
    EndPrimitive();*/
}

void main()
{
    drawNormalSpace(0);
}