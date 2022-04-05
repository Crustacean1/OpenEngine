#include "Renderer.h"
#include "Render.h"
#include "../Shader/Shader.h"
#include <iostream>

using namespace OpenEngine;

Renderer::~Renderer() {}

void Renderer::flush()
{
    if (manager != nullptr)
    {
        manager->renderees[material][mesh].push_back(&object);
        manager->iBuffer.reallocate(manager->renderees[material][mesh].size());
        it = (--manager->renderees[material][mesh].end());
    }
}
void Renderer::setMaterial(Material *mat)
{
    if (mesh != nullptr)
    {
        manager->renderees[material][mesh].erase(it);
    }
    material = mat;
    flush();
}
Material *Renderer::getMaterial()
{
    return material;
}
void Renderer::setMesh(Mesh *_m,Material * _mat)
{
    if (mesh != nullptr)
    {
        manager->renderees[material][mesh].erase(it);
    }
    mesh = _m;
    if(material==nullptr||_mat!=nullptr)
    {
        material = _mat;
    }
    if(mesh!=nullptr)
    {
        flush();
    }
}
Mesh *Renderer::getMesh()
{
    return mesh;
}