#include "Material.h"
#include "../Shader/Shader.h"



void OpenEngine::Material::update()
{
    amb.bind();
    diff.bind();
    spec.bind();
    norm.bind();
    
    shader->set((getName()+".amb"),amb.getUnitID());
    shader->set((getName()+".diff"),diff.getUnitID());
    shader->set((getName()+".spec"),spec.getUnitID());
    shader->set((getName()+".norm"),norm.getUnitID());
    shader->set((getName()+".shininess"),shininess);
}
void OpenEngine::Material::activate()
{
    shader->set("activeMaterialID",(int)getBinding());
}