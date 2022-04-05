#version 420 core

out vec4 rColor;

in vec3 fPos;
in vec3 fNorm;
in vec2 fTex;
in vec3 fParX;
in vec3 fParY; 

struct Material
{
    sampler2D amb;
    sampler2D diff;
    sampler2D spec;
    sampler2D norm;
    float shininess;
};

struct DirectionalLight
{
    int isActive;
    vec3 dir;
    vec3 color;

    float ambient;
    float diffuse;
    float specular;
};
struct PointLight
{
    int isActive;
    vec3 pos;
    vec3 color;

    float ambient;
    float diffuse;
    float specular;
};

vec3 computeLight(PointLight light,vec3 pos,vec3 norm, Material mat)
{
    vec3 result = vec3(0,0,0);
    result += light.ambient * texture(mat.amb,fTex).xyz;

    vec3 lVec = normalize(light.pos-pos);
    result += light.diffuse * texture(mat.diff,fTex).xyz * max(light.diffuse * dot(lVec,norm),0);
    //lVec = -lVec + 2*dot(lVec,norm)*norm;

    result += light.specular * texture(mat.spec,fTex).xyz * pow(max(dot(normalize(lVec+normalize(-pos)),norm),0),mat.shininess);
    return result*texture(mat.diff,fTex).xyz;
}
// TODO add specular maps
vec3 computeLight(DirectionalLight light,vec3 pos,vec3 norm,Material mat)
{
    vec3 result = vec3(0,0,0);
    result += light.ambient * texture(mat.amb,fTex).xyz;
    result += texture(mat.diff,fTex).xyz * light.diffuse *max(0,dot(-light.dir,norm));

    vec3 lVec = normalize(-light.dir);
    result += texture(mat.spec,fTex).xyz * light.specular*pow(max(0,dot(norm,normalize(lVec-normalize(pos)))),mat.shininess);
    return result*light.color;
}

uniform Material materials[16];
uniform PointLight pLights[16];
uniform DirectionalLight dLights[16];

uniform int activeMaterialID = 0;


void main()
{
    vec4 tmp1 = ((texture(materials[activeMaterialID].norm,fTex) * 2) - vec4(1,1,1,0));
    vec3 normal = normalize(vec3((tmp1.x*fParX + tmp1.y*fParY +  tmp1.z*fNorm)));
    //normal = normalize(fNorm);

    rColor = vec4(0,0,0,0);
    //rColor = texture(materials[activeMaterialID].norm,fTex);
    for(int i = 0;i<16;i++)
    {
        if(pLights[i].isActive==0){continue;}
        rColor += vec4(computeLight(pLights[i],fPos,normal,materials[activeMaterialID]),0);
    }
    for(int i = 0;i<16;i++)
    {
        if(dLights[i].isActive==0){continue;}
        rColor += vec4(computeLight(dLights[i],fPos,normal,materials[activeMaterialID]),0);
    }
    //rColor = vec4(normal.xyz,1);
    //rColor = texture(materials[activeMaterialID].norm,fTex);
    //rColor = vec4(fTex.x,fTex.y,0,1);
}