#version 420

out vec4 rColor;

in vec3 fNorm;
in vec2 fTex;
in vec3 fParX;
in vec3 fParY; 

struct Material
{
    sampler2D diff;
    sampler2D spec;
    sampler2D norm;
    float shininess;
};

struct DirectionalLight
{
    vec3 dir;
    vec3 color;

};

float computeDirLight();

uniform Material materials[5];


void main()
{
    vec4 normal = texture(materials[0].norm,fTex) * 2 - vec4(1,1,1,1);
    vec3 res = fParX;

    //res = res*0.5 + 0.5;
    //rColor = texture(materials[0].diff,fTex);
    rColor = vec4(res,1);
    //rColor = vec4(0.5,0.2,0.2,1);

}