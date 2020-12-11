#include "Material.h"
#include "../Shader/Shader.h"
#include "../Loaders/TextureLoader/TextureLoader.h"
#include "../ResourceManager/ResourceManager.h"

void OpenEngine::Material3D::update()
{
    amb->bind();
    diff->bind();
    spec->bind();
    norm->bind();

    shader->set((getName() + ".amb"), amb->getUnitID());
    shader->set((getName() + ".diff"), diff->getUnitID());
    shader->set((getName() + ".spec"), spec->getUnitID());
    shader->set((getName() + ".norm"), norm->getUnitID());
    shader->set((getName() + ".shininess"), shininess);
}
void OpenEngine::Material3D::activate()
{
    update();
    shader->set("activeMaterialID", (int)getBinding());
}
OpenEngine::Material3D::Material3D() : amb(nullptr),diff(nullptr), spec(nullptr), norm(nullptr), shininess(32)
{
    diff = ResourceManager::create<Texture2D>(127,127,127);
    amb = ResourceManager::create<Texture2D>(127,127,127);
    spec = ResourceManager::create<Texture2D>(127,127,127);
    norm = ResourceManager::create<Texture2D>(127,127,127);
}
OpenEngine::CubeMaterial::CubeMaterial()
{
    //cubemap.createFromColor(200,200,200);
}
void OpenEngine::CubeMaterial::update()
{
    cubemap.bind();
    shader->set(getName(),cubemap.getUnitID());
}
void OpenEngine::CubeMaterial::activate()
{
    //update();
}