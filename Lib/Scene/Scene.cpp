#include "Scene.h"

void OpenEngine::Scene::render()
{
    for(const auto & render :renders)
    {
        render->render();
    }
}