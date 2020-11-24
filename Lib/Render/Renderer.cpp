#include "Renderer.h"
#include "Render.h"
#include "../Shader/Shader.h"

using namespace OpenEngine;

int Renderer::getIndexOf(Mesh *_m)
{
    auto it = meshes.begin();
    for (int i = 0; it != meshes.end(); i++, it++)
    {
        if (std::get<1>(*it) == _m)
        {
            return i;
        }
    }
    return -1;
}

void Renderer::setMaterial(Material3D *mat, unsigned int i)
{
    if (!(i < meshes.size()))
    {
        return;
    }
    auto it = meshes.begin();
    std::advance(it, 2);
    dropMesh(i);
    std::get<0>(*it) = mat;
    std::get<2>(*it) = ((Render *)manager)->add(std::get<0>(*it), std::get<1>(*it), &object);
}
Material3D *Renderer::getMaterial(unsigned int i)
{
    if (!(i < meshes.size()))
    {
        return nullptr;
    }
    auto it = meshes.begin();
    advance(it, i);
    return std::get<0>(*it);
}
void Renderer::addMesh(Mesh *_mesh, Material3D *_mat)
{
    meshes.push_back(std::tuple<Material3D *, Mesh *, std::list<Object *>::iterator>(_mat, _mesh, nullptr));
    if (manager != nullptr)
    {
        std::get<2>(meshes.back()) = ((Render *)manager)->add(_mat, _mesh, &object);
    }
}
void Renderer::dropMesh(unsigned int _id)
{
    if (!(_id < meshes.size()))
    {
        return;
    }
    auto it = meshes.begin();
    std::advance(it, _id);
    if (manager != nullptr)
    {
        ((Render *)manager)->drop(std::get<0>(*it), std::get<1>(*it), std::get<2>(*it));
    }
    meshes.erase(it);
}
void Renderer::setMesh(Mesh *_m, unsigned int _id)
{
    if (!(_id < meshes.size()))
    {
        return;
    }
    dropMesh(_id);
    auto it = meshes.begin();
    std::advance(it, _id);
    std::get<1>(*it) = _m;
    if (manager != nullptr)
    {
        std::get<2>(*it) = ((Render *)manager)->add(std::get<0>(*it), std::get<1>(*it), &object);
    }
}
Mesh *Renderer::getMesh(unsigned int _id)
{
    if (!(_id < meshes.size()))
    {
        return nullptr;
    }
    auto it = meshes.begin();
    std::advance(it, _id);
    return std::get<1>(*it);
}
unsigned int Renderer::getMeshesCount()
{
    return meshes.size();
}
void Renderer::assignMeshes()
{
    for (auto &unit : meshes)
    {
        std::get<2>(unit) = ((Render *)manager)->add(std::get<0>(unit), std::get<1>(unit), &object);
    }
}
void Renderer::dropMeshes()
{
    while (meshes.size() > 0)
    {
        dropMesh(0);
    }
}