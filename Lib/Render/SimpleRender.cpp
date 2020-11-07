#include "SimpleRender.h"
#include "Renderer.h"
#include "../Shader/Shader.h"
#include "../Camera/Camera.h"
#include "../Object/Object.h"

void OpenEngine::SimpleRender::render()
{
    for(const auto & pairs : renderers)
    {
        pairs.first->use();

        for(const auto & renderer: pairs.second)
        {
            pairs.first->set("mvp",mainCamera->getMatrix(renderer->getOwner()->getGlobalPosition(),
                                                        renderer->getOwner()->getGlobalRotation(),
                                                        renderer->getOwner()->getGlobalScale()));
            renderer->render();
        }
    }
}