#include "SimpleRender.h"
#include "Renderer.h"
#include "../Shader/Shader.h"
#include "../Camera/Camera.h"
#include "../Object/Object.h"
#include "../Light/Helios.h"


OpenEngine::SimpleRender::SimpleRender(Camera * _cam) : Render(_cam),lightManager(new Helios()){}

void OpenEngine::SimpleRender::render()
{
    glm::mat4 view;
    lightManager->illuminate(mainCamera);

    for(const auto & pairs : renderers)
    {
        pairs.first->use();

        for(const auto & renderer: pairs.second)
        {
            view = mainCamera->getViewMatrix(renderer->object.getGlobalPosition(),
                                                        renderer->object.getGlobalRotation(),
                                                        renderer->object.getGlobalScale());
            pairs.first->set("mvp",mainCamera->getProjectionMatrix() * view);
            pairs.first->set("mv",view);
            renderer->render();
        }
    }
}