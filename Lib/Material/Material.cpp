#include "Material.h"
#include "../Shader/Shader.h"

void OpenEngine::Material3D::update()
{
    amb.bind();
    diff.bind();
    spec.bind();
    norm.bind();

    shader->set((getName() + ".amb"), amb.getUnitID());
    shader->set((getName() + ".diff"), diff.getUnitID());
    shader->set((getName() + ".spec"), spec.getUnitID());
    shader->set((getName() + ".norm"), norm.getUnitID());
    shader->set((getName() + ".shininess"), shininess);
}
void OpenEngine::Material3D::activate()
{
    shader->set("activeMaterialID", (int)getBinding());
}
OpenEngine::Material3D::Material3D() : diff(), spec(), norm(), shininess(32)
{
    diff.createFromColor(127,127,127);
    diff.flush();
    amb.createFromColor(127,127,127);
    amb.flush();
    spec.createFromColor(127,127,127);
    spec.flush();
    norm.createFromColor(127,127,255);
    norm.flush();
}