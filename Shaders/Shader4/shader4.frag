#version 420

out vec4 rColor;

in vec3 fNorm;
in vec2 fTex;
in vec3 fParX;
in vec3 fParY; 

struct DirectionalLight
{

};
struct PointLight
{

};

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
    float shininess;
};

uniform Material materials[5];

void main()
{
    rColor = texture()
}