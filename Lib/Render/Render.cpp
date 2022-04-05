#include "Render.h"
#include "Renderer.h"
#include "../Shader/Shader.h"
#include "../Material/Material.h"
#include "../Object/Object.h"
#include "../Mesh/Mesh.h"
#include "../Camera/Camera.h"
#include "../Light/Helios.h"
#include "../Component/Transform/Transform.h"

//unsigned int OpenEngine::Render3D::mainIndex = 0;
std::map<unsigned int,OpenEngine::Render3D*> OpenEngine::Render3D::managers;

OpenEngine::Render3D::Render3D(Scene * _scene,Camera *_cam) : ComponentManager(_scene), mainCamera(_cam), lightManager(new Helios(_scene)) {}

void OpenEngine::InstantiatingBuffer::reallocate(int i)
{
    if (i + 1 > buff.getSize())
    {
        if (buff.getSize() == 0)
        {
            buff.setBuffer(1);
            return;
        }
        buff.setBuffer(buff.getSize() * 2);
    }
}

void OpenEngine::Render3D::add(Renderer *_renderer)
{
    ComponentManager<Renderer, Render3D>::add(_renderer);
}
OpenEngine::Renderer *OpenEngine::Render3D::drop(Renderer *_renderer)
{
    return ComponentManager<Renderer, Render3D>::drop(_renderer);
}

void OpenEngine::Render3D::render()
{
    glm::mat4 view;
    lightManager->illuminate(mainCamera);
    InstanceMatrix *mv;
    if (mainCamera == nullptr)
    {
        return;
    }

    for (auto &material : renderees)
    {
        if (material.first != nullptr)
        {
            material.first->activate();
            material.first->getShader()->set("proj", mainCamera->getProjectionMatrix());
        }
        for (auto &mesh : material.second)
        {
            mv = iBuffer.buff.getData();
            for (auto &obj : mesh.second)
            {
                (mv++)->mat = mainCamera->getViewMatrix(obj->transform.getGlobalPosition(),
                                                        obj->transform.getGlobalRotation(),
                                                        obj->transform.getGlobalScale());
            }
            mesh.first->bind();
            iBuffer.buff.flush();
            iBuffer.buff.setAttribs();
            material.first->getShader()->use();
            glDrawElementsInstanced(mesh.first->shape, mesh.first->getMeshSize(), GL_UNSIGNED_INT, 0, mesh.second.size());
        }
    }
}