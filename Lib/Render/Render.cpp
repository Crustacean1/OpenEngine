#include "Render.h"
#include "Renderer.h"
#include "../Shader/Shader.h"
#include "../Material/Material.h"
#include "../Object/Object.h"
#include "../Mesh/Mesh.h"
#include "../Camera/Camera.h"
#include "../Light/Helios.h"

OpenEngine::Render3D::Render3D(Camera *_cam) : mainCamera(_cam), lightManager(new Helios()) {}
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
    ComponentManager<Renderer>::add(_renderer);
}
void OpenEngine::Render3D::drop(Renderer *_renderer)
{
    ComponentManager<Renderer>::drop(_renderer);
}

void OpenEngine::Render3D::execute()
{
    glm::mat4 view;
    lightManager->illuminate(mainCamera);
    InstanceMatrix *mv;

    for (auto &material : renderees)
    {
        if (material.first != nullptr)
        {
            material.first->activate();
            material.first->getShader()->set("proj", mainCamera->getProjectionMatrix());
        }
        int i = 0;
        for (auto &mesh : material.second)
        {
            mv = iBuffer.buff.getData();
            for (auto &obj : mesh.second)
            {
                (mv++)->mat = mainCamera->getViewMatrix(obj->getGlobalPosition(),
                                                        obj->getGlobalRotation(),
                                                        obj->getGlobalScale());
            }
            mesh.first->bind();
            iBuffer.buff.flush();
            iBuffer.buff.setAttribs();
            material.first->getShader()->use();
            glDrawElementsInstanced(mesh.first->shape, mesh.first->getMeshSize(), GL_UNSIGNED_INT, 0, mesh.second.size());
        }
    }
}