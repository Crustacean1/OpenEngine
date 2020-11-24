#include "SimpleRender.h"
#include "Renderer.h"
#include "../Shader/Shader.h"
#include "../Camera/Camera.h"
#include "../Object/Object.h"
#include "../Light/Helios.h"
#include "../Material/Material.h"


OpenEngine::SimpleRender::SimpleRender(Camera * _cam) : Render(_cam),lightManager(new Helios()){}

void OpenEngine::SimpleRender::render()
{
    glm::mat4 view;
    lightManager->illuminate(mainCamera);
    InstanceMatrix * mv;

    for(auto & material : renderees)
    {
        material.first->shader->set("proj",mainCamera->getProjectionMatrix());
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
            //iBuffer.buff.setAttribs();
            glDrawElementsInstanced(mesh.first->getShape(),mesh.first->getMeshSize(),GL_UNSIGNED_INT,0,mesh.second.size());
        }
    }
}