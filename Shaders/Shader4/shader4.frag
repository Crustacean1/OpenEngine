#version 420

out vec4 rColor;

in vec3 fPos;
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
    bool active;
    vec3 dir;
    vec3 color;

    float ambient;
    float diffuse;
    float specular;
};
struct PointLight
{
    bool active;
    vec3 pos;
    vec3 color;

    float ambient;
    float diffuse;
    float specular;
};

vec3 computeLight(PointLight light,vec3 pos,vec3 norm, Material mat)
{
    float intensity = 0;
    intensity += light.ambient;

    vec3 lVec = normalize(light.pos-pos);
    intensity += light.diffuse * dot(lVec,norm);
    lVec = -lVec + 2*dot(lVec,norm)*norm;

    intensity += light.specular * pow(max(dot(lVec,normalize(-pos)),0),mat.shininess);
    return intensity*light.color*texture(mat.diff,fTex).xyz;
}

uniform Material materials[16];
uniform PointLight pLights[16];
uniform DirectionalLight dLights[16];

uniform int activeMaterialID = 0;


void main()
{
    vec4 tmp1 = texture(materials[0].norm,fTex) * 2 - vec4(1,1,1,1);
    tmp1 = vec4((tmp1.x*fParX + tmp1.y*fParY + tmp1.z*fNorm),0);
    vec3 normal = normalize(tmp1.xyz);

    rColor = vec4(0,0,0,0);
    for(int i = 0;i<16;i++)
    {
        if(pLights[i].active ==false){continue;}
        rColor += vec4(computeLight(pLights[i],fPos,normal,materials[activeMaterialID]),0);
    }
}