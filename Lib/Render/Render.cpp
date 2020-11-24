#include "Render.h"
#include "Renderer.h"
#include "../Shader/Shader.h"
#include "../Material/Material.h"
#include "../Object/Object.h"
#include "../Mesh/Mesh.h"

void OpenEngine::InstantiatingBuffer::reallocate()
{
    if(buff.getSize()==0)
    {
        buff.setBuffer(1);
        return;
    }
    buff.setBuffer(buff.getSize()*2);
}

std::list<OpenEngine::Object *>::iterator OpenEngine::Render::add(Material *_mat, Mesh *_mesh, Object *_obj)
{
    renderees[_mat][_mesh].push_back(_obj);
    if(!(renderees[_mat][_mesh].size()<iBuffer.buff.getSize()))
    {
        iBuffer.reallocate();
    }
    iBuffer.buff.bind();
    _mesh->bind();
    InstanceMatrix::setAttribs();
    _mesh->unbind();
    return renderees[_mat][_mesh].end()--;
}
void OpenEngine::Render::drop(OpenEngine::Material *_mat, OpenEngine::Mesh *_mesh, std::list<Object *>::iterator it)
{
    if (renderees.find(_mat) != renderees.end())
    {
        if (renderees[_mat].find(_mesh) != renderees[_mat].end())
        {
            renderees[_mat][_mesh].erase(it);
        }
    }
}
void OpenEngine::Render::add(Renderer *_renderer)
{
    ComponentManager<Renderer>::add(_renderer);
    _renderer->assignMeshes();
}
void OpenEngine::Render::drop(Renderer *_renderer)
{
    ComponentManager<Renderer>::drop(_renderer);
    _renderer->dropMeshes();
}