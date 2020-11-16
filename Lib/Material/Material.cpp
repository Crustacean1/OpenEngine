#include "Material.h"
#include "../Shader/Shader.h"

std::string toStr(int a)
{
    std::string res;
    while(a>0)
    {
        res = (char)((a%10)+'0') + res;
        a/=10;
    }
}

void OpenEngine::Material::setId(unsigned int _id)
{
    ID = _id;
    shaderId = "materials["+toStr(ID)+"]";
}

void OpenEngine::Material::update()
{
    diff.bind();
    spec.bind();
    norm.bind();
    
    shader->set((shaderId+".diff").c_str(),diff.getUnitID());
    shader->set((shaderId+".spec").c_str(),spec.getUnitID());
    shader->set((shaderId+".norm").c_str(),norm.getUnitID());
    shader->set((shaderId+".shininess").c_str(),shininess);
}