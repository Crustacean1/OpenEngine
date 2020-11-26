#include "Render.h"
#include "Renderer.h"
#include "../Shader/Shader.h"
#include "../Material/Material.h"
#include "../Object/Object.h"
#include "../Mesh/Mesh.h"
#include "../Camera/Camera.h"
#include "../Light/Helios.h"

OpenEngine::Render3D::Render3D(Camera *_cam) : mainCamera(_cam),lightManager(new Helios()) {}
void OpenEngine::InstantiatingBuffer::reallocate()
{
    if(buff.getSize()==0)
    {
        buff.setBuffer(1);
        return;
    }
    buff.setBuffer(buff.getSize()*2);
}

std::list<OpenEngine::Object *>::iterator OpenEngine::Render3D::add(Material3D *_mat, Mesh *_mesh, Object *_obj)
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
void OpenEngine::Render3D::drop(OpenEngine::Material3D *_mat, OpenEngine::Mesh *_mesh, std::list<Object *>::iterator it)
{
    if (renderees.find(_mat) != renderees.end())
    {
        if (renderees[_mat].find(_mesh) != renderees[_mat].end())
        {
            renderees[_mat][_mesh].erase(it);
        }
    }
}
void OpenEngine::Render3D::add(Renderer *_renderer)
{
    ComponentManager<Renderer>::add(_renderer);
    _renderer->assignMeshes();
}
void OpenEngine::Render3D::drop(Renderer *_renderer)
{
    ComponentManager<Renderer>::drop(_renderer);
    _renderer->dropMeshes();
}

void OpenEngine::Render3D::execute()
{
    glm::mat4 view;
    lightManager->illuminate(mainCamera);
    InstanceMatrix * mv;

    for(auto & material : renderees)
    {
        material.first->update();
        material.first->activate();
        material.first->shader->set("proj",mainCamera->getProjectionMatrix());
        int i = 0;
        for(auto & mesh : material.second)
        {
            mv = iBuffer.buff.getData();
            for(auto & obj : mesh.second)
            {
                (mv++)->mat = mainCamera->getViewMatrix(obj->getGlobalPosition(),
                                                        obj->getGlobalRotation(),
                                                        obj->getGlobalScale());
            }
            mesh.first->bind();
            iBuffer.buff.flush();
            iBuffer.buff.setAttribs();
            material.first->shader->use();
            glDrawElementsInstanced(mesh.first->getShape(),mesh.first->getMeshSize(),GL_UNSIGNED_INT,0,mesh.second.size());
        }
    }
}