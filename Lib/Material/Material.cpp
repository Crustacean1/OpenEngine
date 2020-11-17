#include "Material.h"
#include "../Shader/Shader.h"

std::string toStr(int a)
{
    std::string res;
    do
    {
        res = (char)((a%10)+'0') + res;
        a/=10;
    }

    while(a>0);
    return res;
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
    
    shader->set((shaderId+".diff"),diff.getUnitID());
    shader->set((shaderId+".spec"),spec.getUnitID());
    shader->set((shaderId+".norm"),norm.getUnitID());
    shader->set((shaderId+".shininess"),shininess);
}