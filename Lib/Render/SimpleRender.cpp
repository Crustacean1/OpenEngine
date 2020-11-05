#include "SimpleRender.h"
#include "Renderer.h"
#include "../Shader/Shader.h"

void OpenEngine::SimpleRender::render()
{
    for(const auto & pairs : renderers)
    {
        pairs.first->use();
        for(const auto & renderer: pairs.second)
        {
            renderer->render();
        }
    }
}